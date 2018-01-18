<?php

/**
 * @file
 * This file contains the Rules hooks and functions necessary to make the order
 * related entity, conditions, events, and actions work.
 */

/**
 * Implements hook_rules_action_info().
 */
function compucorp_commerce_civicrm_rules_action_info() {
  $actions['compucorp_commerce_civicrm_action_checkout_complete'] = array(
    'group' => t('Commerce CiviCRM'),
    'label' => t('Action when checkout is complete'),
    'base' => 'compucorp_commerce_civicrm_action_checkout_complete',
    'parameter' => array(
      'commerce_order' => array('type' => 'commerce_order', 'label' => t('Order')),
    ),
  );

  $actions['compucorp_commerce_civicrm_action_order_insert'] = array(
    'group' => t('Commerce CiviCRM'),
    'label' => t('Action when creating a new order'),
    'base' => 'compucorp_commerce_civicrm_action_checkout_complete',
    'parameter' => array(
      'commerce_order' => array('type' => 'commerce_order', 'label' => t('Order')),
    ),
  );

  $actions['compucorp_commerce_civicrm_action_order_update'] = array(
    'group' => t('Commerce CiviCRM'),
    'label' => t('Action when updating an order'),
    'base' => 'compucorp_commerce_civicrm_action_order_update',
    'parameter' => array(
      'commerce_order' => array('type' => 'commerce_order', 'label' => t('Order')),
    ),
  );

  $actions['compucorp_commerce_civicrm_action_order_delete'] = array(
    'group' => t('Commerce CiviCRM'),
    'label' => t('Action when deleting an order'),
    'base' => 'compucorp_commerce_civicrm_action_order_delete',
    'parameter' => array(
      'commerce_order' => array('type' => 'commerce_order', 'label' => t('Order')),
    ),
  );

  $actions['compucorp_commerce_civicrm_action_product_insert'] = array(
    'group' => t('Commerce CiviCRM'),
    'label' => t('Action when creating a new product'),
    'base' => 'compucorp_commerce_civicrm_action_product_insert',
    'parameter' => array(
      'commerce_product' => array('type' => 'commerce_product', 'label' => t('Product')),
    ),
  );

  $actions['compucorp_commerce_civicrm_action_product_update'] = array(
    'group' => t('Commerce CiviCRM'),
    'label' => t('Action when updating a product'),
    'base' => 'compucorp_commerce_civicrm_action_product_update',
    'parameter' => array(
      'commerce_product' => array('type' => 'commerce_product', 'label' => t('Product')),
    ),
  );

  $actions['compucorp_commerce_civicrm_action_product_delete'] = array(
    'group' => t('Commerce CiviCRM'),
    'label' => t('Action when deleting a product'),
    'base' => 'compucorp_commerce_civicrm_action_product_delete',
    'parameter' => array(
      'commerce_product' => array('type' => 'commerce_product', 'label' => t('Product')),
    ),
  );

  return $actions;
}

