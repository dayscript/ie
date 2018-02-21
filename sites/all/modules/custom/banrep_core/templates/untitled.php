<?php

$str = '<p>Profesora asociada Universidad de los Andes</p>

<p>&nbsp;</p>

<p><strong>Resumen:</strong> The effectiveness of public lending to ease credit constraints has been widely studied for microenterprises. Existing evidence for larger firms refers to lending that is significantly subsidized and targeted, so estimated positive effects may reflect poor allocation of public credit. This paper uses uniquely comprehensive data on all non-micro manufacturing firms and all formal credit operations in Colombia to investigate credit constraints to larger businesses taking advantage of a wide, unsubsidized, second-tier (therefore untargeted) government lending program. The program significantly increases beneficiaries’ growth, through longer maturities and closer ties with banks, complementing rather than substituting private lending.</p>

<div>&nbsp;</div>

<p><strong>Fecha:</strong>&nbsp;Jueves, 5 de febrero<br>
	<strong>Lugar:&nbsp;</strong>Salón 407D de Icesi, calle 18 #122-135&nbsp;&nbsp;<br>
	<strong>Hora:</strong>&nbsp;04:30 p.m.<br>
	<strong>Informes:</strong> Silvia Fajardo - Tel. 555 2334, ext 8391<br>
	<strong>Correo:</strong> <a href="mailto:sbfajardo@icesi.edu.co">sbfajardo@icesi.edu.co</a>&nbsp;</p>

<p>&nbsp;</p>

<p><strong>Documento del evento</strong></p>

<p>&nbsp;</p>

<p><img src="http://www.banrep.gov.co/sites/default/files/images/icono-html.gif" style="color:#444444; font-family:Arial,Verdana,Tahoma,DejaVu Sans,sans-serif; font-size:x-small; height:16px; line-height:19.9939994812012px; width:16px"><a href="http://www.banrep.gov.co/sites/default/files/eventos/archivos/sem_11_cali.pdf" target="_blank">Young businesses, entrepreneurship, and the dynamics of employment and output in Colombia’s manufacturing industry</a></p>
';
dpm(get_url($str));

function get_url($text){
	// The Regular Expression filter
	$reg_exUrl = "/(http|https|ftp|ftps)\:\/\/[a-zA-Z0-9\-\.]+\.[a-zA-Z]{2,3}(\/\S*)?/";
	$reg_exUrl = "/(http|https|ftp|ftps)\:\/\/[a-zA-Z0-9\-\.]+\.[a-zA-Z]{2,3}(\/\S*)?/";
	$pattern = '/((?:http|https|ftp|ftps)\:\/\/[a-zA-Z0-9\-\.]+\.[a-zA-Z]{2,3}(?:\/\S*))?/';

	$matches = array();
	preg_match($pattern, $text, $matches);

	return $matches;
}

function hyperlinksAnchored($text) {
    return preg_replace('@(http)?(s)?(://)?(([-\w]+\.)+([^\s]+)+[^,.\s])@', '$1$2$3$4', $text);
}