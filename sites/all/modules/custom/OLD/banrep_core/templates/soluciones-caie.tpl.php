<!-- BEGIN PAGE CONTENT-->
<div class="container">
	<div class="row sortable_portlets" id="sortable_portlets">
		<div class="column sortable" id="row-column-mis-soluciones-caie">
	      <div class="portlet portlet-sortable light no-padding" id="mis-soluciones-caie">
	         <div class="portlet-title hide">
	            <div class="caption font-green-sharp">
	               <i class="icon-speech font-green-sharp"></i>
	               <span class="caption-subject bold uppercase"> <?php echo t('CAIE SOLUTIONS'); ?></span>
	            </div>
	         </div>
	         <div class="portlet-body">
				<div class="dark-blue-box">
				   <div class="row">
 					   <div class="col-lg-3">
 					   	   <h2><?php echo t('CAIE SOLUTIONS'); ?></h2>
 					   </div>
 					   <div class="col-lg-9">
						   <?php foreach ($soluciones_caie as $key => $solucion): ?>
						   	   <?php if(isset($solucion->field_icono_class['und'][0]['value'])): ?>
									<?php $iconclass = $solucion->field_icono_class['und'][0]['value']; ?>
								    <div class="col-lg-2 col-sm-3 col-xs-6">
								      <span class="<?php echo $iconclass; ?> slideToggle" data-tab="solucion-<?php echo $solucion->tid; ?>"></span>
								      <!--<img src="<?php print $image_url; ?>" alt="<?php echo $solucion->name;?>" class="slideToggle" data-tab="solucion-<?php echo $solucion->tid; ?>"-->
								      <span class="tab-name"><?php echo $solucion->name; ?></span>
								    </div>
							   <?php endif; ?>
						   <?php endforeach; ?>
					   </div>
 					   <div class="col-lg-12 solutions-descriptions">
						   <?php foreach ($soluciones_caie as $key => $solucion): ?>
						   	   <?php if(isset($solucion->description)): ?>
									<?php $description = $solucion->description; ?>
									<div class="col-lg-12 col-sm-12 col-xs-12">
									    <div class="row hidden solution" id="solucion-<?php echo $solucion->tid; ?>">
									      <?php echo $description;?>
									    </div>
								    </div>
							   <?php endif; ?>
						   <?php endforeach; ?>
					   </div>
				   </div>
				</div>
	         </div>
	      </div>
	    </div>

	    <!--
		    <div class="column sortable row-column-recursos" id="row-column-noticias">
			    <div class="margin-bottom-22px">
				    <?php //print views_embed_view('noticias', 'soluciones_caie'); ?>
				</div>
			</div>
		-->

	    <div class="column sortable row-column-recursos" id="row-column-galeria-espacios-caie">
		    <div class="margin-bottom-22px">
			    <?php print views_embed_view('espacios_caie', 'espacios_caie'); ?>
			</div>
		</div>

	    <div class="column sortable row-column-recursos" id="row-column-recursos">
	    	<?php render_resources_block(); ?>
	    </div>

	    <!--
		    <div class="column sortable" id="row-column-recursos-documentos-investigacion">
		      <div class="row">
		    	<div class="col-lg-4 recursos-editorial block-dark-gray">
		    		<?php render_resource_editorial_block(); ?>
		    	</div>
		    	<div class="col-lg-8">
		    	    <div class="portlet light-grey box-documentos-investigacion no-padding clearfix">
	    	    		<div class="portlet-title">
					      <div class="caption"><?php echo t('DOCUMENTOS DE APOYO A LA INVESTIGACIÓN');?> </div>
					      <div class="tools pull-right"></div>
					   </div>
					   <div class="portlet-body">
					   		<?php render_support_documents_block(); ?>
					   </div>
		    	    </div>
		    	</div>
		      </div>
		    </div>
		-->
	</div>
</div>
<div class="clearfix"></div>
<!-- END PAGE CONTENT-->
