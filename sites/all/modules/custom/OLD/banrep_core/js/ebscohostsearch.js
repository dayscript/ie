function myScript() {
   var mySelect, x, i;
   x = document.getElementsByClassName("tabs-x");
	for (i = 0; i < x.length; i++){
		x[i].style.display = "none";
	}
	mySelect = document.getElementById("test").value;
		switch (mySelect){
		case "1":
		document.getElementById("tabs-1").style.display="block";
		break;
		case "2":
		document.getElementById("tabs-2").style.display="block";
		break;
		case "3":
		document.getElementById("tabs-3").style.display="block";
		break;
		case "4":
		document.getElementById("tabs-4").style.display="block";
		break;
		case "5":
		document.getElementById("tabs-5").style.display="block";
		break;
		case "52":
		document.getElementById("tabs-52").style.display="block";
		break;
		case "6":
		document.getElementById("tabs-6").style.display="block";
		break;
		case "7":
		document.getElementById("tabs-7").style.display="block";
		break;
		case "8":
		document.getElementById("tabs-8").style.display="block";
		break;
	}
}

function ebscoHostSearchOther(form, buff) {
	var ebscohostsearchtext = chkObject(form.ebscohostsearchtext,'');
	var ebscohostkeywords = chkObject(form.ebscohostkeywords,'');
	var ebscohostsearchsrc = chkObject(form.ebscohostsearchsrc,'');
	var ebscohostsearchmode = chkObject(form.ebscohostsearchmode,'\+AND\+');
	var ebscohostwindow = parseInt(chkObject(form.ebscohostwindow,0));
	var ebscohosturl = chkObject(form.ebscohosturl,'http://search.ebscohost.com/login.aspx?');
	var strAlert="";

	ebscohostsearchtext = encodeURI(ebscohostsearchtext);

	if (ebscohostsearchtext=="")
		strAlert+="Please enter search term(s).\n";

	if (strAlert !== "") {
		alert(strAlert);
		return false;
	}

	//var searchFieldSelector =form["searchFieldSelector"].value;
	var searchFieldSelector = '';
	ebscohosturl+='&bquery='+searchFieldSelector+'+('+ebscohostkeywords+ebscoHostSearchParse(ebscohostsearchtext,ebscohostsearchmode)+')';

	if (ebscohostwindow)
		window.open(ebscohosturl, 'EBSCOhost');
	else
		window.location = ebscohosturl;

	return false;
}

function searchRepo() {
	var text_val = jQuery('#tabs-2 .searchArea #repoSearch').val();
	if(text_val != ''){
		window.location.href = "/publicaciones";
	}else{
		return false;
	}
}

function searchCaieServices(number){
	var text_val = jQuery('#tabs-6 .searchArea #repoSearch').val();
	if(text_val != ''){
		if(number == 1) {
			window.location.href = "/caie/soluciones/resultados-busqueda?global="+text_val+"&tituloser="+text_val;
		}
		else {
			window.location.href = "/caie/recursos/resultados-busqueda?title="+text_val;
		}
	}else{
		return false;
	}
}

function searchSeminars(number){
	var text_val = jQuery('#tabs-7 .searchArea #repoSearch').val();
	if(text_val != ''){
		if(number == 1) {
			window.location.href = "/seminarios/resultados-busqueda?anio%5Bvalue%5D%5Byear%5D="+text_val;
		}
		else {
			window.location.href = "/seminarios/resultados-busqueda?titulo="+text_val;
		}
	}else{
		return false;
	}
}

function searchPublications(number){

	var text_val 	= jQuery('#tabs-8 .searchArea #repoSearch').val();
	var filter 		= document.getElementsByName('publicationFilter');

	if(text_val != '') {
		if(number == 1) {
			for (var i = 0, length = filter.length; i < length; i++)
			{
				if (filter[i].checked) {

					switch( filter[i].value ) {
						case "1" :
									window.location.href = "/publicaciones/lista?keywords="+text_val;
									break;

						case "2" :
									window.location.href = "/publicaciones/lista?titulo="+text_val;
									break;

						case "3" :
									window.location.href = "/publicaciones/lista?autor="+text_val;
									break;
					}

				
				}
			}
		}
		else {
			window.location.href = "/publicaciones/lista?titulo="+text_val;
		}
	}else{
		return false;
	}


}

function searchDatabases(){
	var text_val = jQuery('#tabs-3 .searchArea #repoSearch').val();
	if(text_val != ''){
		window.location.href = "/caie-recursos/bases-de-datos?title="+text_val+"&bv="+text_val;
	}else{
		return false;
	}
}

function searchResearchers(){
	var text_val = jQuery('#tabs-5 .searchArea #repoSearch').val();
	if(text_val != ''){
		window.location.href = "/investigadores?nombre="+text_val;
	}else{
		return false;
	}
}



