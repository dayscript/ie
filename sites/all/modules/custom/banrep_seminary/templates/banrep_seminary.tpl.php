<div class="form-type-select form-item-source cities">
    <?= drupal_render($city_form) ?>
    <i class="fa fa-caret-down" aria-hidden="true"></i>
</div>

<div class="row">
    <div class="columns medium-9 text-container">
        <?= !empty($texts['text-a']) ? 
            $texts['text-a'] :  
            variable_get('custom_text_a', false)
        ?>
    </div>
    <div class="columns medium-3">
        <img src="<?= !empty($images['first']['uri']) ? 
                file_create_url($images['first']['uri']) :  
                file_create_url(file_load(variable_get('custom_image_a', ''))->uri) 
            ?>" 
            class="" alt="<?= !empty($images['first']['alt']) ? $images['first']['alt'] : '' ?>"
        />
    </div>
</div>

<div class="row">
    <div class="columns medium-4">
    <img src="<?= !empty($images['second']['uri']) ? 
                file_create_url($images['second']['uri']) :  
                file_create_url(file_load(variable_get('custom_image_b', ''))->uri) 
            ?>" 
            class="" alt="<?= !empty($images['second']['alt']) ? $images['second']['alt'] : '' ?>"
        />
        <div class="text-container">
            <?= !empty($texts['text-b']) ? 
                $texts['text-b'] :  
                variable_get('custom_text_b', false)
            ?>
        </div>
        <?php if(!empty($name)): ?>
            <div class="button-container">
                <a href="#form" id="btn-postular" class="btn btn-warning" data-remodal-target="modal">
                    Contactar para mas información
                </a>
            </div>
            <div class="remodal clearfix" data-remodal-id="modal">
                <a data-remodal-action="close" class="remodal-close"></a>
                <?= drupal_render($contact_form) ?>
            </div>
        <?php endif; ?>
        <br>
        <hr>
        <h3>Historial</h3>
        <hr>
        <?= views_embed_view('eventos', 'historial', $city) ?>
    </div>
    <div class="columns medium-8">
        <?php if(user_is_logged_in()): ?>
            <?= views_embed_view('eventos', 'page_2', $city) ?>
        <?php else: ?>
            <?= views_embed_view('eventos', 'page_3', $city) ?>
        <?php endif; ?>
    </div>
</div>
