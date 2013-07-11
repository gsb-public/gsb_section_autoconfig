<?php

/**
 * Implements hook_token_info().
 */
function gsb_section_autoconfig_token_info() {
  $info['tokens']['menu']['associated-main-menu-alias'] = array(
    'name' => t('Associated Main Menu Alias'),
    'description' => t('The path alias in the main menu that this menu is associated with.'),
  );

  return $info;
}

/**
 * Implements hook_tokens().
 */
function gsb_section_autoconfig_tokens($type, $tokens, array $data = array(), array $options = array()) {
  $replacements = array();

  if ($type == 'node' && !empty($data['node'])) {
    foreach ($tokens as $name => $original) {
      switch ($name) {
        case 'menu-link:menu:associated-main-menu-alias':
          if (isset($data['node']->menu['menu_name'])) {
            $mlid = $data['node']->menu['menu_name'];
          }
          // If the data doesn't have the menu_name pull it straight from the
          // database.
          else {
            $mlid = db_query("SELECT ml.menu_name from {menu_links} ml where link_path = 'node/" . $data['node']->nid . "'")->fetchField();
          }

          $tid = str_replace('section-', '', $mlid);
          $section = taxonomy_term_load($tid);
          $replacements[$original] = $section->field_workbench_section_path[$data['node']->language][0]['safe_value'];
          break;
      }
    }
  }

  return $replacements;
}
