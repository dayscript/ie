<?php

/**
 * @file
 * Metatag module hooks implementations.
 */

/**
 * Implements hook_metatag_info().
 *
 * @see metatag_metatag_info()
 */
function metatag_google_scholar_metatag_info() {
  $info = array();
  // Define own group for Google Scholar metatags.
  $info['groups']['google_scholar'] = array(
    'label' => t('Google Scholar'),
    'form' => array(
      '#weight' => 3,
      '#collapsed' => TRUE,
    ),
  );

  // Tags. Let's have similar to DC weights.
  $weight = 70;
  $defaults = array(
    'description' => '',
    'class' => 'DrupalTextMetaTag',
    'group' => 'google_scholar',
  );
  $info['tags']['citation_title'] = array(
    'label' => t('Title'),
    'description' => t('Title of the paper. Required for inclusion in Google Scholar.'),
    'weight' => ++$weight,
  ) + $defaults;
  $info['tags']['citation_author'] = array(
    'label' => t('Author'),
    'description' => t('Authors of the paper. At least one author tag is required for inclusion in Google Scholar.'),
    'multiple' => TRUE,
    'weight' => ++$weight,
  ) + $defaults;
  $info['tags']['citation_publication_date'] = array(
    'label' => t('Publication date'),
    'description' => t('The date of publication. Full dates in the 2010/5/12 format if available; or a year alone otherwise. This tag is required for inclusion in Google Scholar.'),
    'weight' => ++$weight,
  ) + $defaults;
  $info['tags']['citation_journal_title'] = array(
    'label' => t('Journal title'),
    'description' => t('Journal title.'),
    'weight' => ++$weight,
  ) + $defaults;
  $info['tags']['citation_issn'] = array(
    'label' => t('ISSN'),
    'description' => t('ISSN.'),
    'weight' => ++$weight,
  ) + $defaults;
  $info['tags']['citation_isbn'] = array(
    'label' => t('ISBN'),
    'description' => t('ISBN.'),
    'weight' => ++$weight,
  ) + $defaults;
  $info['tags']['citation_volume'] = array(
    'label' => t('Volume'),
    'description' => t('Volume.'),
    'weight' => ++$weight,
  ) + $defaults;
  $info['tags']['citation_issue'] = array(
    'label' => t('Issue'),
    'description' => t('Issue.'),
    'weight' => ++$weight,
  ) + $defaults;
  $info['tags']['citation_firstpage'] = array(
    'label' => t('First page'),
    'description' => t('First page.'),
    'weight' => ++$weight,
  ) + $defaults;
  $info['tags']['citation_lastpage'] = array(
    'label' => t('Last page'),
    'description' => t('Last page.'),
    'weight' => ++$weight,
  ) + $defaults;
  $info['tags']['citation_dissertation_institution'] = array(
    'label' => t('Dissertation institution'),
    'description' => t('Dissertation institution.'),
    'weight' => ++$weight,
  ) + $defaults;
  $info['tags']['citation_technical_report_institution'] = array(
    'label' => t('Technical report institution'),
    'description' => t('Technical report institution.'),
    'weight' => ++$weight,
  ) + $defaults;
  $info['tags']['citation_technical_report_number'] = array(
    'label' => t('Technical report number'),
    'description' => t('Technical report number.'),
    'weight' => ++$weight,
  ) + $defaults;
  $info['tags']['citation_pdf_url'] = array(
    'label' => t('PDF URL'),
    'description' => t('PDF URL.'),
    'weight' => ++$weight,
  ) + $defaults;

  return $info;
}
