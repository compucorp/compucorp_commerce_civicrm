## Compucorp Commerce CiviCRM


### Note

This drupal module is originally forked from [commerce civicrm](https://www.drupal.org/project/commerce_civicrm) module but
now it takes a slightly different approach in how syncing from drupal commerce to civicrm happen.


### Intro
When a customer buys something from a [Drupal Commerce](https://www.drupal.org/project/commerce) online shop, this module:

- Creates a CiviCRM contact record if the purchaser doesn't already exist.
- Adds the purchaser to the configured CiviCRM group(s).
- Adds (or updates) a contribution history to their record.
- Sync the products to the configured price set.


The module require you to create a price set on CiviCRM, the reason for this
is to generate proper line items for CiviCRM contributions and
be able to generate proper invoices.
 
Basically all the products on drupal will be synced automatically to 
the configured price set as price set fields.


### Installation

Copy the module to your modules directory then install from drupal or via
drush.


## Configurations

After installing the module, there are a view things need to be configured
before using it :

1. On CiviCRM side, you need to create a new price set in which all the products
will be added automatically, to do this go to : **CiviContribute >> Manage Price Sets**
then click **Add set of Price Fields" button**. Fill the form and click save. It is advised
to pick clear name for the price set that help you to identity its purpose, such as "**Drupal Commerce Products**".

![priceset_create](https://user-images.githubusercontent.com/6275540/35095023-04e5e3f8-fc3f-11e7-8935-0de7053c6da8.gif)


2. Now on drupal side, you need to go to **Store >> Configuration >> CiviCRM**,
From there pick up a "**Contribution type**" (AKA **financial type**), all created contributions
 will be added to this contribution type. After that select the price field you 
 created in the first step. And finally, if you want the created contacts
 to be added automatically to specific group(s) then check any of the listed groups then click save.
 
 
![save_configs](https://user-images.githubusercontent.com/6275540/35095039-0ea4ae4c-fc3f-11e7-88b7-e27344f8bcd7.gif)


 Now everything is ready, you can just start created orders where the module automatically
 will create the contact for the purchaser along with the contribution, and the products
 will be automatically get added to the price set.
 
 Here is a sample created contribution :
 
 <img width="676" alt="2018-01-18 13_00_33-find contributions _ disability rights uk" src="https://user-images.githubusercontent.com/6275540/35094998-f3eb94b2-fc3e-11e7-84d1-2b5adc56b512.png">
 
