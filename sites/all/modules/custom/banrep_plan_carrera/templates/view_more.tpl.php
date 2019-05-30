<?php
  $lista = $variables['list'];
  $label = $variables['label'];
  $titles = $variables['titles'];
?>
<div >
    <a class="test-link" href="#"> <?php print $label?></a>
    <div class="test-link-content hidden">
        <table>
        <?php
            print '<tr>';
            foreach ($titles as $key) {
                print '<td>' . $key . '</td>';
            }
            print '</tr>';
        ?>

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

