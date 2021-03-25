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
           $conTitle = 0;
           
            print '<table class="table-list-pub">';
        
            print '<tr>';
            foreach ($titles as $key) {
                if($contador == 0){
                    print '<th class="text-left">' . $key . '</th>';
                } else {
                    print '<th>' . $key . '</th>';
                }
                $contador++;
                
            }
            print '</tr>';
       
            foreach ($lista as $key => $value) {
                $contItem = 0;
                print '<tr>';
                foreach ($value as $k => $v) {
                    if($contItem == 0){
                        print '<td class="text-left">' . $v . '</td>';
                    } else {
                        print '<td>' . $v . '</td>';
                    }
                    $contItem++;
                }
                print '</tr>';
            }
        print '</table>';
        
        } else {
            print '<h4 class="text-msn">No existen aún publicaciones aprobadas de este tipo</h4>';
        }
    ?>
    </div>
</div>

