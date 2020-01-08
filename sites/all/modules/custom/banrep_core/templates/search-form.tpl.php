<?php
   // @ $data  array with the information data for build form;
?>
<div class="form-container">
  <div class="form-item form-type-select form-item-source">
    <select id="test" onchange="myScript()">
      <?php foreach ($data['options'] as $key => $value) : ?>
      <option value="<?php echo $key?>"><?php echo t( $value ); ?></option>
      <?php endforeach; ?>
    </select>
    <i class="fa fa-caret-down" aria-hidden="true"></i>
  </div>
  <div class="form-item form-type-textfield form-item-keys">
        <div id="tabs-1" class="tabs-x" style="display:block;">
          <form name="direct" action="http://itms.libsteps.com/BR/" method="post">
            <input type="hidden" name="m" value="direct">
            <input type="hidden" name="skey" value="1031">
            <input type="hidden" name="charset" value="utf-8">
            <input type="hidden" name="userid" value="">
            <input type="hidden" name="dbGroup" value="0"/ checked>
            <div class="searchArea">
            <input class="ebscohostsearchtext" type="text" name="text1" size="50">
              <button onclick="DirectSearch();" class="submit"><i class="icon-buscar"></i></button>
              <div id="category1" class="inline-elements">
                <input class="radio" type="radio" name="category1" id="guidedField_0" value="0" checked="checked">
                <label class="label" for="guidedField_0"> <?php echo t('Full Text'); ?></label>
                <input class="radio" type="radio" name="category1" id="guidedField_0" value="2">
                <label class="label" for="guidedField_0"> <?php echo t('Keywords'); ?> </label>
                <input class="radio" type="radio" name="category1" id="guidedField_1" value="1">
                <label class="label" for="guidedField_1"> <?php echo t('Title'); ?> </label>
                <input class="radio" type="radio" name="category1" id="guidedField_2" value="4">
                <label class="label" for="guidedField_2"> <?php echo t('Author'); ?> </label>
              </div>
            </div>
          </form>
        </div>
         <div id="tabs-4" class="tabs-x" style="display:none;">
            <form name="direct" action="http://itms.libsteps.com/BR/" method="post">
               <input type="hidden" name="m" value="direct">
               <input type="hidden" name="skey" value="1031">
               <input type="hidden" name="charset" value="utf-8">
               <input type="hidden" name="userid" value="">
               <input type="hidden" name="dbGroup" value="0"/ checked>
               <div class="searchArea">
                  <input class="ebscohostsearchtext" type="text" name="text1" value="" size="50">
                  <button onclick="DirectSearch();" class="submit"><i class="icon-buscar"></i></button>
                  <div id="category1" class="inline-elements">
                     <input class="radio" type="radio" name="category1" id="guidedField_0" value="1" checked="checked">
                     <label class="label" for="guidedField_0"> Titulo</label>
                     <input class="radio" type="radio" name="category1" id="guidedField_0" value="7">
                     <label class="label" for="guidedField_0"> ISBN</label>
                     <input class="radio" type="radio" name="category1" id="guidedField_1" value="8">
                     <label class="label" for="guidedField_1"> ISSN</label>
                     <input class="radio" type="radio" name="category1" id="guidedField_2" value="9">
                     <label class="label" for="guidedField_2"> Journal</label>
                  </div>
               </div>
            </form>
         </div>
    </div>
  </div>
