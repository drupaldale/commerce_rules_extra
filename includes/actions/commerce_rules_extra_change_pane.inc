<?php
function commerce_rules_extra_change_pane_action_info() {
    return array (
            'label' => t('Change pane properties'),
            'group' => t('Commerce Checkout'),
            'parameter' => array (
                    'pane_id' => array (
                            'type' => 'text',
                            'label' => t('Id of pane to change'),
                            'options list' => 'commerce_rules_extra_get_panes',
                            'restriction' => "input" 
                    ),
                    'page_id' => array (
                            'type' => 'text',
                            'label' => t('Page to move to'),
                            'options list' => 'commerce_rules_extra_get_pages',
                            'default value' => "<same>",
                            'restriction' => "input" 
                    ),
                    'enabled' => array (
                            'type' => 'boolean',
                            'label' => t('Enabled'),
                            'default value' => TRUE,
                            'restriction' => "input" 
                    ),
                    'weight' => array (
                            'type' => 'integer',
                            'label' => t('Weight of pane in the page'),
                            'description' => t("Set to empty to keep pre-defined weight"),
                            'optional' => TRUE,
                            'restriction' => "input" 
                    ) 
            ) 
    );
}

/**
 * Option list callback for commerce_rules_extra_change_pane
 *
 * Return list of checkout pages
 */
function commerce_rules_extra_get_pages() {
    $pages = commerce_checkout_pages();
    $return = array (
            "<same>" => "<do not change>" 
    );
    foreach ( $pages as $page_id => $page ) {
        $return [$page_id] = $page ["title"];
    }
    return $return;
}

/**
 * Option list callback for commerce_rules_extra_change_pane
 *
 * Return list of checkout panes
 */
function commerce_rules_extra_get_panes() {
    $panes = commerce_checkout_panes();
    $return = array ();
    foreach ( $panes as $pane_id => $pane ) {
        $return [$pane_id] = $pane ["title"];
    }
    return $return;
}

/**
 * Callback function for rule commerce_rules_extra_change_pane
 *
 * Store in global variables all properties changes for a pane
 */
function commerce_rules_extra_change_pane($pane_id, $page_id, $enabled, $weight) {
    global $pane_changes;
    if (! $pane_changes)
        $pane_changes = array ();
    $pane_changes[$pane_id] = array (
            "page_id" => ($enabled ? $page_id : "disabled"),
            "enabled" => $enabled,
            "weight" => $weight 
    );
}

/**
 * Show/hide panes when viewing command
 * @param unknown $infos
 * @param unknown $entity_type
 */
function commerce_rules_extra_commerce_order_view_alter(&$infos, $entity_type) {
    global $pane_changes;
    if (! $pane_changes)
        $pane_changes = array ();
        
    $commerce_order = $infos["#entity"];
    //rules_invoke_all('process_checkout_pane', $commerce_order);
        
    foreach ( $pane_changes as $pane_id => $changes ) {
       $field_name = variable_get('commerce_' . $pane_id . '_field', '');
       if (empty($field_name)) {$field_name = $pane_id;}
       if (! array_key_exists($field_name, $infos)) continue;
       if ($changes ["enabled"] == false) {
           unset($infos[$field_name]); //["#access"] = false;
       }
       else if ($changes["weight"] != "") {
          $infos[$field_name]["#weight"] = $changes["weight"];
       }
    }
    
} 