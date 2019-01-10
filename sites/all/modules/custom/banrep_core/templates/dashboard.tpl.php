<?php
	$uid = '';
	global $user;
	$user_is_logged_in = user_is_logged_in();
	if($user_is_logged_in){
		if(isset($user->uid)){
			$uid = $user->uid;
		}
	}
?>
<!-- BEGIN PAGE CONTENT-->
<div class="container">
	<div class="row sortable_portlets" id="sortable_portlets">
		<div class="column sortable" id="row-column-mis-soluciones-caie">
	      <div class="portlet portlet-sortable light no-padding" id="mis-soluciones-caie">
	         <div class="portlet-title hide">
	            <div class="caption font-green-sharp">
	               <i class="icon-speech font-green-sharp"></i>
	               <span class="caption-subject bold uppercase"> MIS SOLUCIONES CAIE</span>
	            </div>
	         </div>
	         <div class="portlet-body">
				<div class="dark-blue-box">
				   <div class="row">
 					   <div class="col-lg-3">
 					   	   <h2>MIS SOLUCIONES CAIE</h2>
 					   </div>
 					   <div class="col-lg-9">

					   </div>
 					   <div class="col-lg-12 solutions-descriptions">

					   </div>
				   </div>
				</div>
	         </div>
	      </div>
	    </div>
	    <div class="column sortable" id="row-column-recursos">
	    	<?php render_resources_block(); ?>
	    </div>
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
	    <div class="column sortable" id="row-column-referencia-especializada-foros">
	      <div class="row">
	    	<div class="col-lg-8">
	    	    <div class="portlet dark-grey dark-portlet no-padding referencia-especializada clearfix">
    	    		<div class="portlet-title">
				      <div class="caption"><?php echo t('REFERENCIA ESPECIALIZADA');?> </div>
				      <div class="tools pull-right"></div>
				   </div>
				   <div class="portlet-body">
				   		<?php render_specialized_reference_block(); ?>
				   </div>
	    	    </div>
	    	</div>
	    	<div class="col-lg-4">
	    		<?php if($user_is_logged_in): ?>
	    			<div class="dashboard-column">
			    		<div class="block-mis-enlaces-recomendados">
					 		<?php print views_embed_view('mis_enlaces_recomendados', 'enlaces_recomendados_privados', $uid); ?>
					  	</div>
				  	</div>
			  	<?php endif; ?>
	    	</div>
	      </div>
	    </div>
	</div>
</div>
<div class="clearfix"></div>
<!-- END PAGE CONTENT-->
