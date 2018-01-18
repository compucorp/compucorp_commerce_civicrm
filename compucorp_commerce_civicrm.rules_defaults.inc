<?php
/**
 * @file
 * Default rules
 */

/**
 * Implements hook_default_rules_configuration().
 */
function compucorp_commerce_civicrm_default_rules_configuration() {
  $rule = rules_reaction_rule();
  $rule->label = t('checkout complete rule');
  $rule->active = TRUE;
  $rule->weight = 3;
  $rule->event('commerce_checkout_complete');
  $rule->action('compucorp_commerce_civicrm_action_checkout_complete', array('commerce_order:select' => 'commerce-order'));
  $configs['compucorp_commerce_civicrm_checkout_complete'] = $rule;

  $rule = rules_reaction_rule();
  $rule->label = t('order insert rule');
  $rule->active = TRUE;
  $rule->weight = 3;
  $rule->event('commerce_order_insert');
  $rule->action('compucorp_commerce_civicrm_action_order_insert', array('commerce_order:select' => 'commerce-order'));
  $configs['compucorp_commerce_civicrm_order_insert'] = $rule;

  $rule = rules_reaction_rule();
  $rule->label = t('order update rule');
  $rule->active = TRUE;
  $rule->event('commerce_order_update');
  $rule->action('compucorp_commerce_civicrm_action_order_update', array('commerce_order:select' => 'commerce-order'));
  $configs['compucorp_commerce_civicrm_order_update'] = $rule;

  $rule = rules_reaction_rule();
  $rule->label = t('order delete rule');
  $rule->active = TRUE;
  $rule->event('commerce_order_delete');
  $rule->action('compucorp_commerce_civicrm_action_order_delete', array('commerce_order:select' => 'commerce-order'));
  $configs['compucorp_commerce_civicrm_order_delete'] = $rule;

  $rule = rules_reaction_rule();
  $rule->label = t('product insert rule');
  $rule->active = TRUE;
  $rule->event('commerce_product_insert');
  $rule->action('compucorp_commerce_civicrm_action_product_insert', array('commerce_product:select' => 'commerce-product'));
  $configs['compucorp_commerce_civicrm_product_insert'] = $rule;

  $rule = rules_reaction_rule();
  $rule->label = t('product update rule');
  $rule->active = TRUE;
  $rule->event('commerce_product_update');
  $rule->action('compucorp_commerce_civicrm_action_product_update', array('commerce_product:select' => 'commerce-product'));
  $configs['compucorp_commerce_civicrm_product_update'] = $rule;

  $rule = rules_reaction_rule();
  $rule->label = t('product delete rule');
  $rule->active = TRUE;
  $rule->event('commerce_product_delete');
  $rule->action('compucorp_commerce_civicrm_action_product_delete', array('commerce_product:select' => 'commerce-product'));
  $configs['compucorp_commerce_civicrm_product_delete'] = $rule;

  $configs = array_merge($configs, compucorp_commerce_civicrm_order_user_creation_rules());

  return $configs;
}

function compucorp_commerce_civicrm_order_user_creation_rules() {
  // Store the customer profile entity info for use in default rules.
  $customer_profile_entity_info = entity_get_info('commerce_customer_profile');

  $rule = rules_reaction_rule();

  $rule->label = t('Assign an anonymous order to a pre-existing user (From new order)');
  $rule->tags = array('Commerce Civicrm');
  $rule->active = TRUE;

  $rule
    ->event('commerce_order_insert')
    ->condition('data_is', array(
      'data:select' => 'commerce-order:uid',
      'op' => '==',
      'value' => '0',
    ))
    ->condition('entity_exists', array(
      'type' => 'user',
      'property' => 'mail',
      'value:select' => 'commerce-order:mail',
    ))
    ->condition('data_is', array(
      'data:select' => 'commerce-order:type',
      'op' => '==',
      'value' => 'commerce_order',
    ))
    ->action('entity_query', array(
      'type' => 'user',
      'property' => 'mail',
      'value:select' => 'commerce-order:mail',
      'limit' => 1,
      'entity_fetched:label' => t('Fetched account'),
      'entity_fetched:var' => 'account_fetched',
    ));

  // Build a loop that updates the order and customer profile uids with the uid
  // from the fetched user account.
  $loop = rules_loop(array(
    'list:select' => 'account-fetched',
    'item:var' => 'list_item',
    'item:label' => t('Current list item'),
    'item:type' => 'user',
  ))
    ->action('data_set', array(
      'data:select' => 'commerce-order:uid',
      'value:select' => 'list-item:uid',
    ));

  // Accommodate any profile types referenced by the order.
  foreach ($customer_profile_entity_info['bundles'] as $type => $data) {
    $instance = field_info_instance('commerce_order', 'commerce_customer_' . $type, 'commerce_order');

    if (!empty($instance)) {
      $loop
        ->action('data_set', array(
          'data:select' => 'commerce-order:' . strtr('commerce-customer-' . $type, '_', '-') . ':uid',
          'value:select' => 'list-item:uid',
        ));
    }
  }

  // Add the loop to the rule as an action.
  $rule->action($loop);

  $rule->weight = 1;

  $rules['commerce_order_convert'] = $rule;

  $rule = rules_reaction_rule();

  $rule->label = t('Create a new account for an anonymous order (From new order)');
  $rule->tags = array('Commerce Civicrm');
  $rule->active = TRUE;

  $rule
    ->event('commerce_order_insert')
    ->condition('data_is', array(
      'data:select' => 'commerce-order:uid',
      'op' => '==',
      'value' => '0',
    ))
    ->condition(rules_condition('entity_exists', array(
      'type' => 'user',
      'property' => 'mail',
      'value:select' => 'commerce-order:mail',
    ))->negate())
    ->condition('data_is', array(
      'data:select' => 'commerce-order:type',
      'op' => '==',
      'value' => 'commerce_order',
    ))
    ->action('entity_create', array(
      'type' => 'user',
      'param_name:select' => 'commerce-order:mail-username',
      'param_mail:select' => 'commerce-order:mail',
      'entity_created:label' => t('Created account'),
      'entity_created:var' => 'account_created',
    ))
    ->action('data_set', array(
      'data:select' => 'account-created:status',
      'value' => 1,
    ))
    ->action('entity_save', array(
      'data:select' => 'account-created',
      'immediate' => 1,
    ))
    ->action('entity_query', array(
      'type' => 'user',
      'property' => 'mail',
      'value:select' => 'commerce-order:mail',
      'limit' => 1,
      'entity_fetched:label' => t('Fetched account'),
      'entity_fetched:var' => 'account_fetched',
    ));

  // Build a loop that updates the order and customer
  // profile uids with the uid from the fetched user account.
  $loop = rules_loop(array(
    'list:select' => 'account-fetched',
    'item:var' => 'list_item',
    'item:label' => t('Current list item'),
    'item:type' => 'user',
  ))
    ->action('data_set', array(
      'data:select' => 'commerce-order:uid',
      'value:select' => 'list-item:uid',
    ));

  // Accommodate any profile types referenced by the order.
  foreach ($customer_profile_entity_info['bundles'] as $type => $data) {
    $instance = field_info_instance('commerce_order', 'commerce_customer_' . $type, 'commerce_order');

    if (!empty($instance)) {
      $loop
        ->action('data_set', array(
          'data:select' => 'commerce-order:' . strtr('commerce-customer-' . $type, '_', '-') . ':uid',
          'value:select' => 'list-item:uid',
        ));
    }
  }

  // Add the loop to the rule as an action.
  $rule->action($loop);

  $rule->weight = 2;

  $rules['commerce_order_new_account'] = $rule;

  return $rules;
}
