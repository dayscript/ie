<div class="form-type-select form-item-source cities">
    <?= drupal_render($city_form) ?>
    <i class="fa fa-caret-down" aria-hidden="true"></i>
</div>

<div class="row">
    <div class="columns medium-9 text-container">
        <?= !empty($texts['text-a']) ? 
            $texts['text-a'] :  
            'Los seminarios de Economía del Banco de la República son espacios en el que investigadores nacionales y extranjeros presentan
            sus trabajos recientes en todas las áreas de economía y finanzas. Se trata de un escenario académico en el que se comunican nuevas
            metodologías y modelos económicos y financieros y se debaten sus implicaciones de política para Colombia y países de la región.'
        ?>
    </div>
    
    <div class="columns medium-3">
        <img src="<?= !empty($images['first']) ? file_create_url($images['first']['uri']) : '/sites/default/files/default-one.jpg' ?>" class="" alt="<?= !empty($images['first']['alt']) ? $images['first']['alt'] : '' ?>"/>
    </div>
</div>

<div class="row">
    <div class="columns medium-4">
        <img src="<?= !empty($images['second']) ? file_create_url($images['second']['uri']) : '/sites/default/files/default-two.jpg' ?>" class="" alt="<?= !empty($images['second']['alt']) ? $images['second']['alt'] : '' ?>"/>
        <div class="text-container">
            <?= !empty($texts['text-b']) ? 
                $texts['text-b'] :  
                'Los investigadores interesados en participar como presentadores en nuestro seminario son bienvenidos a postular sus trabajos
                a través de este portal.'
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
        <?= views_embed_view('eventos', 'page_2', $city) ?>
    </div>
</div>
