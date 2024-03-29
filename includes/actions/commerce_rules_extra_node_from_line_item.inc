<?php
function commerce_rules_extra_node_from_line_item_action_info() {
    return array (
            'label' => t('Get the referencing node from the line item'),
            'group' => t('Commerce Line Item'),
            'parameter' => array (
                    'line_item' => array (
                            'type' => 'commerce_line_item',
                            'label' => t('Commere Line Item') 
                    ) 
            ),
            'provides' => array (
                    'referencing_node' => array (
                            'type' => 'node',
                            'label' => t('Referencing node') 
                    ) 
            ) 
    );
}

/**
 * Callback function for rule commerce_rules_extra_node_from_line_item
 *
 * Return referencing node from line item.
 */
function commerce_rules_extra_node_from_line_item($line_item) {
    $node = NULL;
    
    $entity = $line_item->data['context']['entity'];
    if (isset($entity ['entity_id']) && $entity ['entity_type'] == 'node') {
        $node = node_load($entity ['entity_id']);
    }
    
    return array ('referencing_node' => $node);
}
