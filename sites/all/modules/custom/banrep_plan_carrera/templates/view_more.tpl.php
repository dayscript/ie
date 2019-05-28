<?php
  $lista = $variables['list'];
  $label = $variables['label'];
  $titles = $variables['titles'];
?>
<div >
    <a class="test-link" href="#"> Lista de Publicaciones</a>
    <div class="test-link-content hidden">
        <table>
        <tr>
            <th>Titulo</th>
            <th>Fecha de aprobado</th>
            <th>Puntos</th>

        </tr>

        <?php
            foreach ($lista as $key => $value) {
                print '<tr>';
                foreach ($value as $k => $v) {
                    print '<td>' . $v . '</td>';
                }
                print '</tr>';
            }
            ?>

    </table>
    </div>
</div>

