<?php
/**
 * @file
 * Returns the HTML for a single Drupal page.
 *
 * Complete documentation for this file is available online.
 * @see https://drupal.org/node/1728148
 */
?>

<div id="page" class="site">
  <div class="site-inner">
    <header class="header" role="banner">
      <div class="header__top clearfix">
        <div class="container">
          <div class="row">
            <div class="col-lg-9">
              <div class="menu-top-menu">
                <?php $block = module_invoke('menu', 'block_view', 'menu-top-menu');
                      print render($block['content']); ?>
              </div>
            </div>
            <div class="col-lg-3 user-zone">
              <?php
                $block = module_invoke('banrep_core', 'block_view', 'br_user_top_zone');
                print render($block['content']);
              ?>
            </div>
          </div>
        </div>
      </div>

      <div class="header__brand clearfix">
        <div class="container">
          <div class="row">
            <div class="col-lg-12 header__brand_wrapper">
              <?php if(!$logged_in): ?>
                <div class="row user-login-pass hidden">
                  <?php
                    $block = module_invoke('banrep_core', 'block_view', 'br_login_pass');
                    print render($block['content']);
                  ?>
                </div>
              <?php endif; ?>

              <?php if ($logo): ?>
                <a href="http://www.banrep.gov.co" title="<?php print t('Home'); ?>" rel="home" class="header__logo"><img src="<?php print $logo; ?>" alt="<?php print t('Home'); ?>" class="header__logo-image" /></a>
              <?php endif; ?>

              <?php if ($site_name || $site_slogan): ?>
                <div class="header__name-and-slogan">
                  <?php if ($site_name): ?>
                    <h1 class="header__site-name">
                      <a href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>" class="header__site-link" rel="home"><span><?php print $site_name; ?></span></a>
                    </h1>
                  <?php endif; ?>

                  <?php if ($site_slogan): ?>
                    <div class="header__site-slogan"><?php print $site_slogan; ?></div>
                  <?php endif; ?>
                </div>
              <?php endif; ?>
              <?php $block = module_invoke('locale', 'block_view', 'language');
                            print render($block['content']); ?>
              <?php print render($page['header']); ?>
            </div>
          </div>
        </div>
      </div>
      <div class="header__navbar clearfix">
        <div class="container">
          <div class="row row1">
            <a href="#skip-link" class="visually-hidden visually-hidden--focusable" id="main-menu" tabindex="-1">Back to top</a>
            <div class="col-lg-10 navbar__menu">
              <?php if ($main_menu): ?>
                <nav class="main-menu" role="navigation">
                  <?php
                  print theme('links__system_main_menu', array(
                    'links' => $main_menu,
                    'attributes' => array(
                      'class' => array('navbar', 'clearfix'),
                    ),
                    'heading' => array(
                      'text' => t('Main menu'),
                      'level' => 'h2',
                      'class' => array('visually-hidden'),
                    ),
                  )); ?>
                </nav>
              <?php endif; ?>
            </div>
            <div class="col-lg-2 navbar__search_link">
              <a href="#" title=""><?php echo t('Search'); ?></a>
            </div>
          </div>
          <div class="row">
            <div class="navbar__search_form col-lg-12">
                <?php print render($page['navigation']); ?>
            </div>
          </div>
        </div>
      </div>
    </header>

    <div id="content" class="site-content">
      <?php
        // Render the sidebars to see if there's anything in them.
        $sidebar_first  = render($page['sidebar_first']);
        $sidebar_second = render($page['sidebar_second']);
        // Decide on layout classes by checking if sidebars have content.
        $content_class = 'col-lg-12';
        $sidebar_first_class = $sidebar_second_class = '';
        if ($sidebar_first && $sidebar_second):
          $content_class = 'col-lg-4';
          $sidebar_first_class = 'col-lg-4';
          $sidebar_second_class = 'col-lg-4';
        elseif ($sidebar_second):
          $content_class = 'col-lg-8';
          $sidebar_second_class = 'col-lg-4';
        elseif ($sidebar_first):
          $content_class = 'col-lg-8';
          $sidebar_first_class = 'col-lg-4';
        endif;
      ?>
      <div class="container">
        <div class="row">
          <?php if ($page['highlighted']): ?>
            <div class="destacado clearfix">
              <?php print render($page['highlighted']); ?>
            </div>
          <?php endif; ?>
          <div id="main-content" class="main-content">
            <?php if ($sidebar_first): ?>
              <aside class="<?php print $sidebar_first_class; ?>" role="complementary">
                <?php print $sidebar_first; ?>
              </aside>
            <?php endif; ?>

            <main class="<?php print $content_class; ?>" role="main">
              <?php print $breadcrumb; ?>
              <a href="#skip-link" class="visually-hidden visually-hidden--focusable" id="main-content">Back to top</a>
              <?php print $messages; ?>
              <?php print render($tabs); ?>
              <?php print render($page['help']); ?>
              <?php if ($action_links): ?>
                <ul class="action-links"><?php print render($action_links); ?></ul>
              <?php endif; ?>
              <?php print render($page['content']); ?>
              <?php print $feed_icons; ?>
            </main>

            <?php if ($sidebar_second): ?>
              <aside class="<?php print $sidebar_second_class; ?>" role="complementary">
                <?php print $sidebar_second; ?>
              </aside>
            <?php endif; ?>

            <?php if ($page['content_bottom']): ?>
              <div class="content-bottom clearfix">
                <div class="lg-12">
                  <?php print render($page['content_bottom']); ?>
                </div>
              </div>
            <?php endif; ?>
          </div>
        </div>
      </div>
    </div>

    <footer id="footer" class="site-footer">
      <div class="footer__footer">
        <div class="container">
          <?php print render($page['footer']); ?>
        </div>
      </div>
    </footer>
  </div>
</div>

<?php print render($page['bottom']); ?>
