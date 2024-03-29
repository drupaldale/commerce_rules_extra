<?php

/**
 *  Implements hook_rules_event_info()
 **/
function commerce_rules_extra_rules_event_info() {
    global $cre_includes;
    foreach ( $cre_includes ["events"] as $file ) {
        $rule = basename($file, ".inc");
        $f = $rule . "_event_info";
        $events [$rule] = $f();
    }
    
    return $events;
}

/**
 * Implements hook_rules_conditions_info()
 */
function commerce_rules_extra_rules_condition_info() {
    global $cre_includes;
    foreach ( $cre_includes ["conditions"] as $file ) {
        $rule = basename($file, ".inc");
        $f = $rule . "_condition_info";
        $conditions [$rule] = $f();
    }
    
    return $conditions;
}

/**
 * Implements hook_rules_action_info().
 */
function commerce_rules_extra_rules_action_info() {
    global $cre_includes;
    $actions = array ();
    foreach ( $cre_includes ["actions"] as $file ) {
        $rule = basename($file, ".inc");
        $f = $rule . "_action_info";
        $actions [$rule] = $f();
    }
    
    return $actions;
}

