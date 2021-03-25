<div class="row seminary-register-container">
    <div class="columns medium-9">
        <h3>Seminario seleccionado: <?= $seminary ?></h3>
        <h3>Fecha: <?= $date ?></h3>
    </div>
    <div class="columns medium-3">
        <img src="<?= !empty($image) ? file_create_url($image) : '/sites/default/files/default-one.jpg' ?>" class="" alt="<?= !empty($imag_alt) ? $image_alt : 'Imagen de referencia' ?>"/>
    </div>
    <div class="columns large-12 form-container">
        <?= drupal_render(drupal_get_form('banrep_seminary_register_form')) ?>
    </div>
</div>