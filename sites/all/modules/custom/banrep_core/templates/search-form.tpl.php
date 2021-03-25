<?php
   // @ $data  array with the information data for build form;
?>
<div class="form-container">
  <div class="form-item form-type-select form-item-source">
    <select id="test" onchange="myScript()">
      <?php $show_options = ['1', '5', '7', '8']; ?>
      <?php if(!strpos($_SERVER['REQUEST_URI'], 'caie')): ?>
        <?php foreach ($data['options'] as $key => $value) : ?>
          <?php foreach ($show_options AS $option) : ?>
            <?php if($option == $key): ?>
              <option value="<?php echo $key?>"><?php echo t( $value ); ?></option>
            <?php endif; ?>
          <?php endforeach; ?>
        <?php endforeach; ?>
      <?php else: ?>
        <?php foreach ($data['options'] as $key => $value) : ?>
          <option value="<?php echo $key?>"><?php echo t( ($value == 'Búsqueda General') ? 'Escriba el término de búsqueda' : $value ); ?></option>
        <?php endforeach; ?>
      <?php endif; ?>
    </select>
    <i class="fa fa-caret-down" aria-hidden="true"></i>
  </div>
  <div class="form-item form-type-textfield form-item-keys">
    <div id="tabs-1" class="tabs-x">
      <form name="direct" id="direct-search" 
        action="<?php echo strpos($_SERVER['REQUEST_URI'], 'caie') ? 
          'https://s443-itms-libsteps-com.br.lsproxy.net/BR/' : 
          '/busqueda-general/general?' ?>" 
        <?php strpos($_SERVER['REQUEST_URI'], 'caie') ? print 'target="_blank" method="get"' : print 'method="post"' ?>
      >
        <input type="hidden" name="m" value="direct">
        <input type="hidden" name="skey" value="1031">
        <input type="hidden" name="charset" value="utf-8">
        <input type="hidden" name="userid" value="">
        <input type="hidden" name="dbGroup" value="0" checked="">
        <div class="searchArea" style="min-width:520px">
          <input id="ebscohostsearchtext" class="ebscohostsearchtext" name="text1" type="text" size="50" />
          <button onclick="" class="submit" id="direct-search-button"><i class="icon-buscar"></i></button>
          <div id="guidedFieldSelectors" class="inline-elements">
            <?php if(!strpos($_SERVER['REQUEST_URI'], 'caie')): ?>
              <input type="radio" name="category1" value="6" checked="">
              <label class="label" for="guidedField_6"> <?php echo t('General'); ?></label>
            <?php endif; ?>
            <input type="radio" name="category1" value="0">
            <label class="label" for="guidedField_0"> <?php echo t('Full text'); ?></label>
            <input type="radio" name="category1" value="2">
            <label class="label" for="guidedField_0"> <?php echo t('Keywords'); ?></label>
            <input type="radio" name="category1" value="1">
            <label class="label" for="guidedField_1"> <?php echo t('Title'); ?></label>
            <input type="radio" name="category1" value="4">
            <label class="label" for="guidedField_2"> <?php echo t('Author'); ?></label>
            <?php if(!strpos($_SERVER['REQUEST_URI'], 'caie')): ?>
              <input type="radio" name="category1" value="5">
              <label class="label" for="guidedField_5"> <?php echo t('JEL'); ?></label>
            <?php endif; ?>
          </div>
          <span id="alert-text" style="color:#860024;font-size:0.9rem;"></span>         
        </div>
        <div id="limiterblock" style="display:none;">
          <div id="limitertitle"><?php echo t('Limit Results'); ?></div>
          <div class="limiter">
            <input type="checkbox" id="chkFullText" name="chkFullText" checked="checked" />
            <label for="chkFullText"><?php echo t('Full Text'); ?></label>
          </div>
          <div class="limiter">
            <input type="checkbox" id="chkCatalogOnly" name="chkCatalogOnly" />
            <label for="chkCatalogOnly"><?php echo t('Only Catalog'); ?></label>
          </div>
        </div>
      </form>
    </div>
    <div id="tabs-3" class="tabs-x" style="display:none;">
      <form id="sbBD">
        <div class="searchArea">
          <input id="repoSearch" class="ebscohostsearchtext" name="ebscohostsearchtext" type="text" size="50" />
          <button onclick="searchDatabases(); return false;" class="submit"><i class="icon-buscar"></i></button>
        </div>
      </form>
    </div>
    <div id="tabs-4" class="tabs-x" style="display:none;">
      <form name="direct" id="direct-search" 
        action="<?php echo strpos($_SERVER['REQUEST_URI'], 'caie') ? 
          'https://s443-itms-libsteps-com.br.lsproxy.net/BR/' : 
          '/busqueda-general/texto-destacado?' ?>" 
        <?php strpos($_SERVER['REQUEST_URI'], 'caie') ? print 'target="_blank" method="get"' : print 'method="post"' ?>
      >
        <input type="hidden" name="m" value="direct">
        <input type="hidden" name="skey" value="1031">
        <input type="hidden" name="charset" value="utf-8">
        <input type="hidden" name="userid" value="">
        <input type="hidden" name="dbGroup" value="0"/ checked>
        <div class="searchArea">
          <input class="ebscohostsearchtext" type="text" name="text1" value="" size="50">
          <button onclick="DirectSearch(1);" class="submit" id="direct-search-button"><i class="icon-buscar"></i></button>

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
    <div id="tabs-5" class="tabs-x" style="display:none;">
      <form id="sbIG">
        <div class="searchArea">
          <input id="repoSearch" class="ebscohostsearchtext" name="ebscohostsearchtext" type="text" size="50" />
          <button onclick="searchResearchers(); return false;" class="submit"><i class="icon-buscar"></i></button>
        </div>
      </form>
    </div>
    <div id="tabs-52" class="tabs-x" style="display:none;">
      <form id="sbIG">
        <div class="searchArea">
          <input id="repoSearch" class="ebscohostsearchtext" name="ebscohostsearchtext" type="text" size="50" />
          <button onclick="searchGroups(); return false;" class="submit"><i class="icon-buscar"></i></button>
        </div>
      </form>
    </div>

    <div id="tabs-6" class="tabs-x" style="display:none;">
      <form id="sbSC">
        <div class="searchArea">
          <input id="repoSearch" class="ebscohostsearchtext" name="ebscohostsearchtext" type="text" size="50" />
          <button onclick="searchCaieServices(1); return false;" class="submit"><i class="icon-buscar"></i></button>
          <div id="caieFilters" class="inline-elements">
            <input id="caiesol" class="radio" type="radio" name="caieFilter" id="solutions" value="1"
              checked="checked" />
            <label class="label" for="caiesol"> <?php echo t('Solutions'); ?></label>
            <input id="caieres" class="radio" type="radio" name="caieFilter" id="resources" value="2" />
            <label class="label" for="caieres"> <?php echo t('Resources'); ?></label>
          </div>
        </div>
      </form>
    </div>

    <div id="tabs-7" class="tabs-x" style="display:none;">
      <form id="sbSS">
        <div class="searchArea">
          <input id="repoSearch" class="ebscohostsearchtext" name="ebscohostsearchtext" type="text" size="50" />
          <button onclick="searchSeminars(1); return false;" class="submit"><i class="icon-buscar"></i></button>
          <div id="seminarFilters" class="inline-elements">
            <input id="seminaryear" class="radio" type="radio" name="seminarFilter" value="1" checked="checked" />
            <label class="label" for="seminaryear"> <?php echo t('Year'); ?></label>
            <input id="seminartitle" class="radio" type="radio" name="seminarFilter" value="2" />
            <label class="label" for="seminartitle"> <?php echo t('Title'); ?></label>
            <div class="error-wrapper"></div>
          </div>
        </div>
      </form>
    </div>

    <div id="tabs-8" class="tabs-x" style="display:none;">
      <form id="sbESPE">
        <div class="searchArea">
          <input id="repoSearch" class="ebscohostsearchtext" name="ebscohostsearchtext" type="text" size="50" />
          <button onclick="searchESPE(1); return false;" class="submit"><i class="icon-buscar"></i></button>
          <div id="seminarFilters" class="inline-elements">
            <input class="radio" type="radio" name="EspeSelector" id="espe_0" value="kw" />
            <label class="label" for="espe_0"> <?php echo t('Keywords'); ?></label>
            <input class="radio" type="radio" name="EspeSelector" id="espe_1" value="tt" />
            <label class="label" for="espe_1"> <?php echo t('Title'); ?></label>
            <input class="radio" type="radio" name="EspeSelector" id="espe_2" value="at" />
            <label class="label" for="espe_2"> <?php echo t('Author'); ?></label>
            <div class="error-wrapper"></div>
          </div>
        </div>
      </form>
    </div>
  </div>
</div>
