<?php
  $lista = $variables['list'];
  $label = $variables['label'];
  $titles = $variables['titles'];
?>
<div >
    <a class="test-link" href="#"> <?php print $label?></a>
    <div class="test-link-content hidden">
    <?php
        if(!empty($lista)){
           
            print '<table>';
        
            print '<tr>';
            foreach ($titles as $key) {
                print '<td>' . $key . '</td>';
            }
            print '</tr>';
       
            foreach ($lista as $key => $value) {
                print '<tr>';
                foreach ($value as $k => $v) {
                    print '<td>' . $v . '</td>';
                }
                print '</tr>';
            }
            

        print '</table>';
        
        } else {
            print '<h4>No existen aún publicaciones aprobadas de este tipo</h4>';
        }
    ?>
    </div>
</div>

