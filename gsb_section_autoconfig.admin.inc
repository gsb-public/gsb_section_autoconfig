<?php

function gsb_section_autoconfig_form() {
  $node_types = node_type_get_types();

  $options = array();
  foreach ($node_types as $node_type) {
    $options[$node_type->type] = $node_type->name;
  }

  $form['test'] = array(
    '#value' => 'Does this work?',
  );

  $form['gsb_section_autoconfig_node_types'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Autoassign Menus to These Node Types'),
    '#options' => $options,
    '#default_value' => variable_get('gsb_section_autoconfig_node_types', array()),
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save configuration'),
  );

  return $form;
}

/**
 *
 */
function gsb_section_autoconfig_form_submit($form, &$form_state) {
  $form_state['values']['gsb_section_autoconfig_node_types'] = array_filter($form_state['values']['gsb_section_autoconfig_node_types']);
  system_settings_form_submit($form, $form_state);
}
