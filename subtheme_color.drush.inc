<?php

/**
 * Implements hook_drush_command().
 */
function subtheme_color_drush_command() {

    $commands['subtheme_color'] = array(
        'description' => 'Subtheme color',
        'aliases' => array('stc'),
        'arguments' => array(
            'palette' => 'Color palette in json format',
        ),
        'options' => array(
        ),
        'examples' => array(
            'drush stc \'{"top": "#4a4a4a"}\'' => 'Set the "top" color',
        ),
    );

    return $commands;
}

/**
 * Drush command logic.
 * drush_[COMMAND_NAME]().
 */
function drush_subtheme_color($jsonPalette = '') {
    if (!$jsonPalette) {
        drush_print('error: there is no colors');
        return;
    }
    $newPalette = json_decode($jsonPalette, true);
    if (!is_array($newPalette)) {
        drush_print('error: error decoding json');
        return;
    }
    $theme_bartik_settings = variable_get('theme_bartik_settings');
    $oldPalette = $theme_bartik_settings['palette'];
    $form_state = array(
        'values' => array(
            'info' => $theme_bartik_settings['info'],
            'theme' => 'bartik',
            'palette' => array_merge($oldPalette, $newPalette)
        )
    );
    color_scheme_form_submit(null, $form_state);
    drush_print('done');
}