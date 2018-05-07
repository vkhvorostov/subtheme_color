<?php

/**
 * Implements hook_drush_command().
 */
function subtheme_color_drush_command() {

    $commands['subtheme_color'] = array(
        'description' => 'Subtheme color',
        'aliases' => array('stc'),
        'arguments' => array(
            'theme' => 'Theme machine name',
            'palette' => 'Color palette in json format',
        ),
        'options' => array(
        ),
        'examples' => array(
            'drush stc bartik \'{"top": "#4a4a4a"}\'' => 'Set the "top" color for "bartik" theme',
        ),
    );

    return $commands;
}

/**
 * Drush command logic.
 * drush_[COMMAND_NAME]().
 */
function drush_subtheme_color($themeMachineName = '', $jsonPalette = '') {
    if (!$themeMachineName) {
        drush_print('error: theme machine name is required');
        return;
    }
    if (!$jsonPalette) {
        drush_print('error: there is no palette colors to set');
        return;
    }
    $newPalette = json_decode($jsonPalette, true);
    if (!is_array($newPalette)) {
        drush_print('error: error decoding json');
        return;
    }
    $theme_settings = variable_get('theme_' . $themeMachineName . '_settings');
    if (!$theme_settings || !is_array($theme_settings['palette'])) {
        drush_print('error: error reading existing theme palette');
        return;
    }
    $oldPalette = $theme_settings['palette'];
    $form_state = array(
        'values' => array(
            'info' => $theme_settings['info'],
            'theme' => $themeMachineName,
            'palette' => array_merge($oldPalette, $newPalette)
        )
    );
    color_scheme_form_submit(null, $form_state);
    drush_print('done');
}