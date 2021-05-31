<div id="map-container" class="columns medium-8">
    <img ismap src="/sites/default/files/colombia-mapa.png" usemap="#image-map" class="jq_maphilight" id="image-map">

    <map name="image-map">
        <!-- Para class medium-12
            <area class="cree-circle" id="villavicencio" target="_blank" alt="CREE-Suroriente - Villavicencio" title="CREE-Suroriente - Villavicencio" href="CREE-Suroriente - Villavicencio" coords="466,694,29" shape="circle">
            <area class="cree-circle" id="ibague" target="_blank" alt="CREE-Centro - Ibagué" title="CREE-Centro - Ibagué" href="CREE-Centro - Ibagué" coords="335,657,17" shape="circle">
            <area class="cree-circle" id="cartagena" target="_blank" alt="CREE-Costa Caribe - Cartagena" title="CREE-Costa Caribe - Cartagena" href="CREE-Costa Caribe - Cartagena" coords="318,189,18" shape="circle">
            <area class="cree-circle" id="manizales" target="_blank" alt="CREE-Eje Cafetero - Manizales" title="CREE-Eje Cafetero - Manizales" href="CREE-Eje Cafetero - Manizales" coords="309,612,10" shape="circle">
            <area class="cree-circle" id="medellin" target="_blank" alt="CREE-Noroccidente - Medellín" title="CREE-Noroccidente - Medellín" href="CREE-Noroccidente - Medellín" coords="312,528,30" shape="circle">
            <area class="cree-circle" id="bucaramanga" target="_blank" alt="CREE-Nororiente - Bucaramanga" title="CREE-Nororiente - Bucaramanga" href="CREE-Nororiente - Bucaramanga" coords="494,455,16" shape="circle">
            <area class="cree-circle" id="cali" target="_blank" alt="CREE-Suroccidente - Cali" title="CREE-Suroccidente - Cali" href="CREE-Suroccidente - Cali" coords="247,734,15" shape="circle">
        -->
        <!-- Para class medium-8 -->
        <area class="cree-circle" id="bogota" target="_blank" alt=" Unidad de Investigaciones" title=" Unidad de Investigaciones" href="<?= $centers['Bogotá'] ?>" coords="<?= $coords['Bogotá'] ?>" shape="circle">
        <area class="cree-circle" id="tunja" target="_blank" alt="Departamento de Estudios de Política Económica (DEPE)" title="Departamento de Estudios de Política Económica (DEPE)" href="<?= $centers['Tunja'] ?>" coords="<?= $coords['Tunja'] ?>" shape="circle">
        <area class="cree-circle" id="cartagena" target="_blank" alt="CREE-Costa Caribe - Cartagena" title="CREE-Costa Caribe - Cartagena" href="<?= $centers['Cartagena'] ?>" coords="<?= $coords['Cartagena'] ?>" shape="circle">
        <area class="cree-circle" id="bucaramanga" target="_blank" alt="CREE-Nororiente - Bucaramanga" title="CREE-Nororiente - Bucaramanga" href="<?= $centers['Bucaramanga'] ?>" coords="<?= $coords['Bucaramanga'] ?>" shape="circle">
        <area class="cree-circle" id="medellin" target="_blank" alt="CREE-Noroccidente - Medellín" title="CREE-Noroccidente - Medellín" href="<?= $centers['Medellín'] ?>" coords="<?= $coords['Medellín'] ?>" shape="circle">
        <area class="cree-circle" id="manizales" target="_blank" alt="CREE-Eje Cafetero - Manizales" title="CREE-Eje Cafetero - Manizales" href="<?= $centers['Manizales'] ?>" coords="<?= $coords['Manizales'] ?>" shape="circle">
        <area class="cree-circle" id="ibague" target="_blank" alt="CREE-Centro - Ibagué" title="CREE-Centro - Ibagué" href="<?= $centers['Ibagué'] ?>" coords="<?= $coords['Ibagué'] ?>" shape="circle">
        <area class="cree-circle" id="cali" target="_blank" alt="CREE-Suroccidente - Cali" title="CREE-Suroccidente - Cali" href="<?= $centers['Cali'] ?>" coords="<?= $coords['Cali'] ?>" shape="circle">
        <area class="cree-circle" id="villavicencio" target="_blank" alt="CREE-Suroriente - Villavicencio" title="CREE-Suroriente - Villavicencio" href="<?= $centers['Villavicencio'] ?>" coords="<?= $coords['Villavicencio'] ?>" shape="circle">
    </map>
</div>
<div id="list-container" class="columns medium-4">
    <?= drupal_render($form) ?>
</div>