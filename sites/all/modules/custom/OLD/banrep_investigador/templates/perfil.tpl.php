<?php $usuario = $variables['usuario']; ?>
<div class="col-lg-9">
  <div class="row">
    <div class="col-lg-3">
      imagen
    </div>
    <div class="col-lg-9">
      <h1 class="nombre"><?php echo $usuario->field_full_name['und'][0]['value']; ?></h1>
      <div class="cargo"><?php echo _banrep_obtener_nombre_tid($usuario->field_position['und'][0]['tid']); ?></div>
    </div>
  </div>
</div>
<div class="col-lg-3">
lateral
</div>
