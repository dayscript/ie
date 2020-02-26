<?php
  $login_form = $variables['login_form'];
  $pass_form = $variables['pass_form'];
?>


<div class="col-lg-12 banrep-user-login-pass clearfix">
  <div class="banrep-user-login-form">
    <div class="col-lg-9">
      <?php print($login_form); ?>
      <div class="user__login-linkform">
        <a href="#" id="show-recover" class="link"><?php echo t('Forgot your password?'); ?></a>
      </div>
    </div>
  </div>
  <div class="banrep-user-pass-form hidden">
    <div  class="col-lg-7">
      <?php print($pass_form); ?>
      <div class="user__login-linkform">
        <a href="#" id="show-login" class="link"><?php echo t('Log In'); ?></a>
      </div>
    </div>
  </div>
</div>
