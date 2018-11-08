<div class="form-container">
    <div class="form-item form-type-select form-item-source">
    <select id="test" onchange="myScript()">
      <option value="1"><?php echo t('Global Search'); ?></option>
      <option value="3"><?php echo t('Databases'); ?></option>
      <option value="4"><?php echo t('Books and Journals'); ?></option>
      <option value="5"><?php echo t('Researchers'); ?></option>
      <option value="6"><?php echo t('CAIE'); ?></option>
      <option value="7"><?php echo t('Seminars'); ?></option>
      <option value="8"><?php echo t('ESPE'); ?></option>
    </select>
    <i class="fa fa-caret-down" aria-hidden="true"></i>
  </div>
  <div class="form-item form-type-textfield form-item-keys">

         <div id="tabs-1" class="tabs-x">
            <form id="ebscohostCustomSearchBox" action="" onsubmit="return ebscoHostSearchGo(this);" method="post">
               <input id="ebscohostwindow" name="ebscohostwindow" type="hidden" value="1" />
               <input id="ebscohosturl" name="ebscohosturl" type="hidden" value="http://search.ebscohost.com/login.aspx?direct=true&site=eds-live&scope=site&type=0&custid=s5094900&groupid=main&profid=eds&mode=bool&lang=es&authtype=cookie,ip" />
               <input id="ebscohostsearchsrc" name="ebscohostsearchsrc" type="hidden" value="db" />
               <input id="ebscohostsearchmode" name="ebscohostsearchmode" type="hidden" value="+" />
               <input id="ebscohostkeywords" name="ebscohostkeywords" type="hidden" value="" />
               <div class="searchArea">
                  <input id="ebscohostsearchtext" class="ebscohostsearchtext" name="ebscohostsearchtext" type="text" size="50"  />
                  <button class="submit"><i class="icon-buscar"></i></button>
                  <div id="guidedFieldSelectors" class="inline-elements">
                     <input class="radio" type="radio" name="searchFieldSelector" id="guidedField_0" value="" checked="checked" />
                     <label class="label" for="guidedField_0"> <?php echo t('Keywords'); ?></label>
                     <input class="radio" type="radio" name="searchFieldSelector" id="guidedField_1" value="TI" />
                     <label class="label" for="guidedField_1"> <?php echo t('Title'); ?></label>
                     <input class="radio" type="radio" name="searchFieldSelector" id="guidedField_2" value="AU" />
                     <label class="label" for="guidedField_2"> <?php echo t('Author'); ?></label>
                  </div>
               </div>
               <div id="limiterblock" style="display:none;">
                  <div id="limitertitle"><?php echo t('Limit Results'); ?></div>
                  <div class="limiter" >
                     <input type="checkbox" id="chkFullText" name="chkFullText" checked="checked" />
                     <label for="chkFullText"><?php echo t('Full Text'); ?></label>
                  </div>
                  <div class="limiter" >
                     <input type="checkbox" id="chkCatalogOnly" name="chkCatalogOnly"  />
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
            <form id="sbPeriodici" action="" onsubmit="return ebscoHostSearchOther(this);" method="post">
               <div class="searchArea">
                 <input id="ebscohostwindow" name="ebscohostwindow" type="hidden" value="1" />
                 <input id="ebscohosturl" name="ebscohosturl" type="hidden" value="http://search.ebscohost.com/login.aspx?direct=true&site=eds-live&scope=site&type=44&db=edspub&custid=s5094900&amp;groupid=main&amp;profid=eds&amp;mode=bool&amp;lang=es&amp;authtype=ip" />
                 <input id="ebscohostsearchsrc" name="ebscohostsearchsrc" type="hidden" value="db" />
                 <input id="ebscohostsearchmode" name="ebscohostsearchmode" type="hidden" value="+" />
                 <input id="ebscohostkeywords" name="ebscohostkeywords" type="hidden" value="" />
                 <input id="ebscohostsearchtext" class="ebscohostsearchtext" name="ebscohostsearchtext" type="text" size="50" placeholder="<?php echo t('Enter a title, subject or ISSN / ISBN'); ?>"/>
                 <button class="submit"><i class="icon-buscar"></i></button>
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
                     <input id="caiesol" class="radio" type="radio" name="caieFilter" id="solutions" value="1" checked="checked" />
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
