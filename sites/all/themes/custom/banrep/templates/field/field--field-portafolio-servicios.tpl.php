<div class="field-name-field-portafolio-servicios">
  <div class="field-items">
    <?php foreach ($items as $delta => $item): ?>
      <div class="field-item">
        <?php print render($item); ?>
      </div>
    <?php endforeach; ?>
  </div>
</div>
