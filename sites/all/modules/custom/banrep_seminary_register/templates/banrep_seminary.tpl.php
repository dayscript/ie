<div class="row">
    <div class="columns medium-8 text-container">
        <div>
            <?= !empty($texts['text-a']) ?
                $texts['text-a'] :
                variable_get('custom_text_a', false)
            ?>
        </div>
        <div class="row">
            <?php foreach($tematicas AS $tid => $tematica): ?>
                <div class="columns medium-3">
                    <a href="<?= current_path() .'?tematica='. $tematica['tid'] ?> " class="theme-button button" style="background-color:<?= $tematica['color'] ?>">
                        <?= $tematica['name'] ?>
                    </a>
                </div>
            <?php endforeach; ?>
        </div>

        <div class="row">
            <?php if(user_is_logged_in()): ?>
                <?= views_embed_view('eventos', 'page_2', $city) ?>
            <?php else: ?>
                <?= views_embed_view('eventos', 'page_3', $city) ?>
            <?php endif; ?>
        </div>
    </div>

    <div class="columns medium-4">
        <!-- <img src="<?= !empty($images['second']['uri']) ?
                file_create_url($images['second']['uri']) :
                file_create_url(file_load(variable_get('custom_image_b', ''))->uri)
            ?>"
            class="" alt="<?= !empty($images['second']['alt']) ? $images['second']['alt'] : '' ?>"
        /> -->
        <div class="text-container">
            <?= !empty($texts['text-b']) ?
                $texts['text-b'] :
                variable_get('custom_text_b', false)
            ?>

        </div>

            <div class="button-container" style="text-align: center;">
                <a href="#form" id="btn-postular" class="btn btn-warning" data-remodal-target="modal" >
                    Postular
                </a>
            </div>
            <div class="remodal clearfix" data-remodal-id="modal">
                <a data-remodal-action="close" class="remodal-close"></a>
                <?= drupal_render($contact_form) ?>
            </div>

        <br>
        <hr>
        <h3>Historial</h3>
        <hr>
        <?= views_embed_view('eventos', 'historial', $city) ?>
    </div>
</div>
