<?php

require_once dirname(__FILE__) . '/../banrep_migration_helper.inc';
class PublicacionesNodeMigration extends Migration {
  private static $internos = array('arley barandica-villegas'=>'abaranvi@banrep.gov.co','andres alberto cabrales-urdaneta'=>'acabraur@banrep.gov.co','alvaro david carmona-duarte'=>'acarmodu@banrep.gov.co','adolfo leon cobo-serna'=>'acoboser@banrep.gov.co','karina acosta'=>'acosta.kd@gmail.com','aaron levi garavito-acosta'=>'agaravac@banrep.gov.co','alejandra ximena gonzalez-ramirez'=>'agonzara@banrep.gov.co','alexander guarin-lopez'=>'aguarilo@banrep.gov.co','ana maria iregui-bohorquez'=>'airegubo@banrep.gov.co','angelica maria lizarazo-cuellar'=>'alizarcu@banrep.gov.co','andres mauricio martinez-jimenez'=>'amartiji@banrep.gov.co','adrian martinez-osorio'=>'amartios@banrep.gov.co','constanza martinez-ventura'=>'amartive@banrep.gov.co','adolfo enrique meisel-roca'=>'ameisero@banrep.gov.co','andres mauricio mendoza-espinosa'=>'amendoes@banrep.gov.co','amilcar mojica-pimiento'=>'amojicpi@banrep.gov.co','adriana paola morales-acevedo'=>'amoralac@banrep.gov.co','andres mauricio sanchez-jabba'=>'amsj@uw.edu','alida del rosario narvaez-daza'=>'anarvada@banrep.gov.co','andrea sofia otero-cortes'=>'as.otero114@gmail.com','adriana sierra-todaro'=>'asierrto@banrep.gov.co','adriana torres-saavedra'=>'atorresa@banrep.gov.co','ana maria tribin-uribe'=>'atribiur@banrep.gov.co','ana maria yaruro-jaime'=>'ayarurja@banrep.gov.co','camila agudelo-rivera'=>'caguderi@banrep.gov.co','cesar anzola-bravo'=>'canzolbr@banrep.gov.co','carlos david ardila-dueñas'=>'cardildu@banrep.gov.co','clorith angelica bahos-olivera'=>'cbahosol@banrep.gov.co','carlos leonardo barreto-vargas'=>'cbarreva@banrep.gov.co','carlos alberto cadena-silva'=>'ccadensi@banrep.gov.co','camilo alberto cardenas-hurtado'=>'ccardehu@banrep.gov.co','carlos mario espinosa-rico'=>'cespinri@banrep.gov.co','camilo gonzalez'=>'cgonzasa@banrep.gov.co','clark junior granger-castaño'=>'cgrangca@banrep.gov.co','camila andrea guzman-paez'=>'cguzmapa@banrep.gov.co','carlos a. huertas-campos'=>'chuertca@banrep.gov.co','carlos eduardo leon-rincon'=>'cleonrin@banrep.gov.co','clara lia machado-franco'=>'cmachafr@banrep.gov.co','carlos alberto medina-durango'=>'cmedindu@banrep.gov.co','cesar augusto muñoz-ocampo'=>'cmunozoc@banrep.gov.co','carlos david murcia-bustos'=>'cmurcibu@banrep.gov.co','cristian camilo porras-alarcon'=>'cporraal@banrep.gov.co','christian manuel posso-suarez'=>'cpossosu@banrep.gov.co','carolina ramirez-rodriguez'=>'cramirro@banrep.gov.co','camilo alberto restrepo-valencia'=>'crestrva@banrep.gov.co','cristiam leonardo rincon-ramirez'=>'crincora@banrep.gov.co','carlos alberto suarez-medina'=>'csuareme@banrep.gov.co','carlos julio varela-barrios'=>'cvarelba@banrep.gov.co','carmiña ofelia vargas-riaño'=>'cvargari@banrep.gov.co','diego felipe cifuentes-paris'=>'dcifuepa@banrep.gov.co','deicy johana cristiano-botia'=>'dcristbo@banrep.gov.co','daniel esteban diaz-posada'=>'ddiazpos@banrep.gov.co','dairo ayiber estrada'=>'destrada@banrep.gov.co','david camilo lopez-valenzuela'=>'dlopezva@banrep.gov.co','diego alejandro martinez-cruz'=>'dmarticr@banrep.gov.co','dora alicia mora-perez'=>'dmoraper@banrep.gov.co','daniel esteban osorio-rodriguez'=>'dosoriro@banrep.gov.co','daisy johana pacheco-bernal'=>'dpachebe@banrep.gov.co','daniel parra amado'=>'dparraam@banrep.gov.co','diego arturo rodriguez-guzman'=>'drodrigu@banrep.gov.co','diego hernan rodriguez-hernandez'=>'drodrihe@banrep.gov.co','diego alejandro rojas-prieto'=>'drojaspr@banrep.gov.co','diego alberto sandoval-herrera'=>'dsandohe@banrep.gov.co','daniel ricardo vergara-fonseca'=>'dvergafo@banrep.gov.co','edgar caicedo-garcia'=>'ecaicega@banrep.gov.co','esteban gomez'=>'egomezgo@banrep.gov.co','eliana rocio gonzalez-molano'=>'egonzamo@banrep.gov.co','enrique lopez enciso'=>'elopezen@banrep.gov.co','enrique montes'=>'emonteur@banrep.gov.co','eduardo yanquen-briñez'=>'eyanqubr@banrep.gov.co','freddy hernan cepeda lopez'=>'fcepedlo@banrep.gov.co','felipe clavijo ramirez'=>'fclavira@banrep.gov.co','fredy gamboa-estrada'=>'fgamboes@banrep.gov.co','franz alonso hamann salcedo'=>'fhamansa@banrep.gov.co','francisco javier lasso valderrama'=>'flassova@banrep.gov.co','ferney niño-rodriguez'=>'fninorod@banrep.gov.co','fabio ortega'=>'fortegca@banrep.gov.co','francisco javier villadiego-yanes'=>'fvillaya@banrep.gov.co','francisco alejandro vivas-ramos'=>'fvivasra@banrep.gov.co','gustavo adolfo betin-benedetti'=>'gbetinbe@banrep.gov.co','gladys andrea galeano-rodriguez'=>'ggalearo@banrep.gov.co','araminta gabriela garzon-perilla'=>'ggarzope@banrep.gov.co','german alberto muñoz-bravo'=>'gmunozbr@banrep.gov.co','gladys patiño-franco'=>'gpatinfr@banrep.gov.co','gerson javier perez v.'=>'gperezva@banrep.gov.co','gloria ines sarmiento-becerra'=>'gsarmibe@banrep.gov.co','gerardo alberto villa-duran'=>'gvilladu@banrep.gov.co','hernan rincon-castro'=>'hrincoca@banrep.gov.co','hernando vargas-herrera'=>'Hvargahe@banrep.gov.co','hector manuel zarate-solano'=>'hzaratso@banrep.gov.co','ivonne lissete alvarez-mojica'=>'ialvarmo@banrep.gov.co','ivan gonzalo higuera-mendieta'=>'ihigueme@banrep.gov.co','ignacio lozano-espitia'=>'ilozanes@banrep.gov.co','ingrid marcela sierra-herrera'=>'isierrhe@banrep.gov.co','ivan dario torroledo-peña'=>'itorrope@banrep.gov.co','juan sebastian amador torres'=>'jamadoto@banrep.gov.co','jhorland ayala-garcia'=>'jayalaga@banrep.gov.co','jesus antonio bejarano rojas'=>'jbejarro@banrep.gov.co','santos javier beltran-peñuela'=>'jbeltrpe@banrep.gov.co','jack alan bohn-silberman'=>'jbohmsil@banrep.gov.co','jean pietro bonaldi-varon'=>'jbonalva@banrep.gov.co','jaime bonet moron'=>'jbonetmo@banrep.gov.co','juan esteban carranza'=>'jcarraro@banrep.gov.co','jorge humberto cely-fernandez'=>'jcelyfe@banrep.gov.co','jaime andres collazos rodriguez'=>'jcollaro@banrep.gov.co','juan pablo cote-baron'=>'jcotebar@banrep.gov.co','juan jose echavarria'=>'jechavso@banrep.gov.co','julio escobar'=>'jescobpo@banrep.gov.co','juliana gamboa-arbelaez'=>'jgamboar@banrep.gov.co','jaider garces-carrascal'=>'jgarceca@banrep.gov.co','jose eduardo gomez-gonzalez'=>'jgomezgo@banrep.gov.co','javier guillermo gomez-pineda'=>'jgomezpi@banrep.gov.co','joao alejandro hernandez-calderon'=>'jhernaca@banrep.gov.co','jorge luis hurtado-guarin'=>'jhurtagu@banrep.gov.co','juan manuel julio-roman'=>'jjulioro@banrep.gov.co','juan s. lemus-esquivel'=>'jlemuses@banrep.gov.co','juan manuel lima-ortega'=>'jlimaort@banrep.gov.co','jorge ricardo mariño-martinez'=>'jmarinma@banrep.gov.co','juan sebastian mariño-montaña'=>'jmarinmo@banrep.gov.co','juan carlos mendoza gutierrez de piñeres'=>'jmendogu@banrep.gov.co','juan camilo meneses-cortes'=>'jmenesco@banrep.gov.co','javier ivan miguelez-marquez'=>'jmiguema@banrep.gov.co','jorge niño cuervo'=>'jninocue@banrep.gov.co','jair n. ojeda-joya'=>'jojedajo@banrep.gov.co','juan jose ospina-tejeiro'=>'jospinte@banrep.gov.co','julian a. parra-polania'=>'jparrapo@banrep.gov.co','julian mauricio perez-amaya'=>'jperezam@banrep.gov.co','jose hernan piñeros-gordo'=>'jpinergo@banrep.gov.co','jorge enrique ramos forero'=>'jramosfo@banrep.gov.co','juan sebastian rojas-moreno'=>'jrojasmo@banrep.gov.co','jose vicente romero-chamorro'=>'jromerch@banrep.gov.co','julio enrique romero-prieto'=>'jromerpr@banrep.gov.co','johana andrea sanabria-dominguez'=>'jsanabdo@banrep.gov.co','jessica dayana suret-leguizamon'=>'jsuretle@banrep.gov.co','jorge andres tamayo'=>'jtamayo8@gmail.com','jorge hernan toro cordoba'=>'jtorocor@banrep.gov.co','jhon edwar torres-gorron'=>'jtorrego@banrep.gov.co','javier yabrudy-vega'=>'jyabruve@banrep.gov.co','karelys katina guzman-finol'=>'katinafinol4@gmail.com','kimberly rojas-silva'=>'krojassi@banrep.gov.co','karen astrid rubio-ramirez'=>'krubiora@banrep.gov.co','luis eduardo arango thomas'=>'larangth@banrep.gov.co','leonardo bonilla'=>'lbonilme@banrep.gov.co','luis hernan calderon-lopez'=>'lcaldelo@banrep.gov.co','lina cardona-sosa'=>'lcardoso@banrep.gov.co','luz adriana florez'=>'lflorefl@banrep.gov.co','luis armando galvis-aponte'=>'lgalviap@banrep.gov.co','lucas wilfried hahn-de castro'=>'lhahndca@banrep.gov.co','ligia alba melo-becerra'=>'lmelobec@banrep.gov.co','luis fernando melo-velandia'=>'lmelovel@banrep.gov.co','leonardo fabio morales'=>'lmoralzu@banrep.gov.co','lina vanessa patiño-echeverri'=>'lpatinec@banrep.gov.co','luis alejandro rojas-bernal'=>'lrojasbe@banrep.gov.co','luisa fernanda silva-escobar'=>'lsilvaes@banrep.gov.co','lisseth adriana yaya-garzon'=>'lyayagar@banrep.gov.co','maria aguilera diaz'=>'maguildi@banrep.gov.co','margarita rosa cabra-garcia'=>'mcabraga@banrep.gov.co','maria camila casas-lozano'=>'mcasaslo@banrep.gov.co','maria mercedes collazos'=>'mcollaga@banrep.gov.co','margarita maria gafaro-gonzalez'=>'mgafargo@banrep.gov.co','manuel dario hernandez-bejarano'=>'mhernabe@banrep.gov.co','maria alejandra hernandez-montes'=>'mhernamo@banrep.gov.co','martha rosalba lopez-piñeros'=>'mlopezpi@banrep.gov.co','maria fernanda meneses-gonzalez'=>'mmenesgo@banrep.gov.co','maria alejandra olarte-delgado'=>'molartde@banrep.gov.co','maria alejandra prieto-sanchez'=>'mprietsa@banrep.gov.co','maria teresa ramirez'=>'mramirgi@banrep.gov.co','mario andres ramos-veloza'=>'mramosve@banrep.gov.co','maria fernanda reyes-roa'=>'mreyesro@banrep.gov.co','monica zoraida rodriguez-arenas'=>'mrodriar@banrep.gov.co','marco antonio ruiz-gil'=>'mruizgil@banrep.gov.co','mauricio villamizar-villegas'=>'mvillavi@banrep.gov.co','nilsa yadira alzate-muñeton'=>'nalzatmu@banrep.gov.co','nestor javier espinosa-rodriguez'=>'nespinro@banrep.gov.co','nicolas martinez-cortes'=>'nmartico@banrep.gov.co','norberto rodriguez n.'=>'nrodrini@banrep.gov.co','nicolas alejandro rubio-rubio'=>'nrubioru@banrep.gov.co','nestor miguel sarmiento-paipilla'=>'nsarmipa@banrep.gov.co','oscar hernan bautista-montero'=>'obautiva@banrep.gov.co','orlando chipatecua-peralta'=>'ochipape@banrep.gov.co','oscar fernando jaulin-mendez'=>'ojaulime@banrep.gov.co','ovidio gustavo ramirez-vanegas'=>'oramirva@banrep.gov.co','orlando andres rubio-velandia'=>'orubiove@banrep.gov.co','oscar mauricio valencia-arana'=>'ovalenar@banrep.gov.co','octavio antonio zuluaga-rivera'=>'ozuluari@banrep.gov.co','pamela cardozo'=>'pcardoor@banrep.gov.co','pablo emilio gonzalez-gomez'=>'pgonzago@banrep.gov.co','pedro alfonso sorza-murcia'=>'psorzamu@banrep.gov.co','philip rory symington-alzate'=>'psymingt@banrep.gov.co','rafael fernando alvarez-romero'=>'ralvarro@banrep.gov.co','rosemary barcos-robles'=>'rbarcoro@banrep.gov.co','ramon eduardo hernandez-ortega'=>'rhernaor@banrep.gov.co','rocio mora quiñones'=>'rmoraqu@banrep.gov.co','rafael alfonso rodriguez-mora'=>'rrodrimo@banrep.gov.co','santiago gamba-santamaria'=>'sgambasa@banrep.gov.co','sebastian giraldo-gonzalez'=>'sgiralgo@banrep.gov.co','sara stephanie gonzalez-rivadeneira'=>'sgonzari@banrep.gov.co','sergio alejandro hernandez-diaz'=>'shernadi@banrep.gov.co','stefany moreno-burbano'=>'smorenbu@banrep.gov.co','sandra isabel salamanca-gil'=>'ssalamgi@banrep.gov.co','sebastian sanin-restrepo'=>'ssaninre@banrep.gov.co','santiago david segovia-baquero'=>'ssegovba@banrep.gov.co','tatiana a. mora-arbelaez'=>'tmoraarb@banrep.gov.co','tatiana venegas-karpf'=>'tvenegka@banrep.gov.co','viviana alejandra alfonso c.'=>'valfonco@banrep.gov.co','victor manuel mendez-villamizar'=>'vmendevi@banrep.gov.co','wilmer osvaldo martinez-rivera'=>'wmartiri@banrep.gov.co','william ivan moreno-jimenez'=>'wmorenji@banrep.gov.co','yurany hernandez-turca'=>'yhernatu@banrep.gov.co','yuri carolina reina-aranza'=>'yreinaar@banrep.gov.co','yesenia silva-diaz'=>'ysilvadi@banrep.gov.co',);
  private static $externos = array('davinson stev abril salcedo'=>TRUE,'ronald acevedo'=>TRUE,'fayber alfonso acosta pardo'=>TRUE,'luisa f. acuña roa'=>TRUE,'carlos alberto alba'=>TRUE,'david aldana'=>TRUE,'alexander alegria castellanos'=>TRUE,'viviana alfonso'=>TRUE,'gloria alonso'=>TRUE,'julio cesar alonso'=>TRUE,'andres alvarez'=>TRUE,'daphne alvarez'=>TRUE,'jorge alvis'=>TRUE,'carlos andres amaya'=>TRUE,'laura andrade-pardo'=>TRUE,'laura angel'=>TRUE,'f. angulo-brown'=>TRUE,'elizabeth aponte'=>TRUE,'mery e. aponte mariño'=>TRUE,'felipe arango'=>TRUE,'juan pablo arango'=>TRUE,'carlos alberto arango-arango'=>TRUE,'maria angelica arbelaez'=>TRUE,'luz karine ardila'=>TRUE,'javier e. ardila garcia'=>TRUE,'julian arevalo b.'=>TRUE,'andres felipe arias'=>TRUE,'fernando arias'=>TRUE,'mauricio arias'=>TRUE,'fabio alberto arias arbelaez'=>TRUE,'carolina aristizabal'=>TRUE,'maria clara aristizabal restrepo'=>TRUE,'dalma sofia ariza-hernandez'=>TRUE,'maria angelica arosemena'=>TRUE,'ali miguel arrieta'=>TRUE,'jose santiago arroyo mina'=>TRUE,'carolina arteaga'=>TRUE,'arturo jose galindo'=>TRUE,'orazio attanasio'=>TRUE,'mauricio avella gomez'=>TRUE,'rodrigo avella'=>TRUE,'oscar avila'=>TRUE,'juliana avila velez'=>TRUE,'javier avila mahecha'=>TRUE,'oscar ivan avila montealegre'=>TRUE,'joao pedro azevedo'=>TRUE,'jorge balat'=>TRUE,'carlos andres ballesteros r'=>TRUE,'mette ersbak bang nielsen'=>TRUE,'adolfo barajas'=>TRUE,'juan david baron'=>TRUE,'oscar becerra'=>TRUE,'oscar reinaldo becerra camargo'=>TRUE,'juan bedoya'=>TRUE,'juan guillermo bedoya ospina'=>TRUE,'begoña gonzalez'=>TRUE,'luis v. bejarano-bejarano'=>TRUE,'german beltran r.'=>TRUE,'paula andrea beltran-saavedra'=>TRUE,'joaquin bernal'=>TRUE,'miguel bernal'=>TRUE,'ricardo bernal fandiño'=>TRUE,'camila bernal mattos'=>TRUE,'ron j. berndsen'=>TRUE,'jenny berthel'=>TRUE,'yanneth rocio betancourt'=>TRUE,'rocio betancourt-garcia'=>TRUE,'bonaldi pietro'=>TRUE,'pietro bonaldi'=>TRUE,'gabriela bonilla'=>TRUE,'alison l. booth'=>TRUE,'santiago borrero'=>TRUE,'hector alberto botello peñaloza'=>TRUE,'jesus botero'=>TRUE,'martha bottia'=>TRUE,'yassine bouhdaouiz'=>TRUE,'david bounie'=>TRUE,'lidia adriana braunstein'=>TRUE,'brayan rojas'=>TRUE,'christian bustamante'=>TRUE,'christian david bustamante amaya'=>TRUE,'juan c. bustos-pelaez'=>TRUE,'carlos caballero'=>TRUE,'gustavo caballero'=>TRUE,'enrique cabrera'=>TRUE,'wilmar alexander cabrera rodriguez'=>TRUE,'carlos cadena'=>TRUE,'santiago caicedo'=>TRUE,'santiago cajiao raigosa'=>TRUE,'a. calvo hernandez'=>TRUE,'sergio camelo'=>TRUE,'jacobo campo robledo'=>TRUE,'alvaro augusto campos'=>TRUE,'guillermo cangrejo'=>TRUE,'carlos gustavo cano'=>TRUE,'laura capera'=>TRUE,'ernesto cardenas'=>TRUE,'mauricio cardenas'=>TRUE,'carlos humberto cardona'=>TRUE,'julio cesar cardona'=>TRUE,'nathali cardozo alvarado'=>TRUE,'cristian oswaldo carmona-sanchez'=>TRUE,'alberto carrasquilla'=>TRUE,'andres fernando carreño'=>TRUE,'bladimir carrillo'=>TRUE,'andres carvajal'=>TRUE,'camila casas'=>TRUE,'elkin castaño'=>TRUE,'jessica fernanda castaño lavado'=>TRUE,'francesca castellani'=>TRUE,'mauricio castillo'=>TRUE,'freddy h. castro'=>TRUE,'giovanni alfonso castro lancheros'=>TRUE,'john castro-pantoja'=>TRUE,'jorge cely'=>TRUE,'laura cepeda emiliani'=>TRUE,'daniel cerquera'=>TRUE,'fernando a. chalarca'=>TRUE,'roberto chang'=>TRUE,'alejandro charry'=>TRUE,'luisa f. charry'=>TRUE,'ximena chavarro-sanchez'=>TRUE,'manolo chavez'=>TRUE,'edwin chirivi'=>TRUE,'c-f chung'=>TRUE,'sergio clavijo'=>TRUE,'deborah cobb-clark'=>TRUE,'alvaro concha'=>TRUE,'jose gregorio contreras'=>TRUE,'patricia correa'=>TRUE,'adriana corredor'=>TRUE,'diana m. cortazar gomez'=>TRUE,'costas milas'=>TRUE,'deicy cristiano-botia'=>TRUE,'p. l. curto-risso'=>TRUE,'luciano de castro'=>TRUE,'leonidas e. de la rosa'=>TRUE,'maria dolores de la mata'=>TRUE,'david delgado'=>TRUE,'ana maria diaz'=>TRUE,'laura catalina diaz-barreto'=>TRUE,'federico j. diez'=>TRUE,'ximena dueñas herrera'=>TRUE,'henry duque'=>TRUE,'jonathan eaton'=>TRUE,'jose ignacio echeverri castro'=>TRUE,'juan carlos echeverry'=>TRUE,'martina eschelbach'=>TRUE,'diana carolina escobar'=>TRUE,'jose fernando escobar r.'=>TRUE,'hadi salehi esfahani'=>TRUE,'maria del pilar esguerra umaña'=>TRUE,'marcela eslava'=>TRUE,'alexandra espinosa'=>TRUE,'miguel espinosa'=>TRUE,'juan andres espinosa-torres'=>TRUE,'ana maria estrada'=>TRUE,'raul anibal feliz'=>TRUE,'leopoldo fergusson'=>TRUE,'david fernandez'=>TRUE,'andres fernandez'=>TRUE,'cristina fernandez'=>TRUE,'diana fernandez'=>TRUE,'ricardo ffrench-davis'=>TRUE,'maria paola figueroa'=>TRUE,'maria lucia florez-jimenez'=>TRUE,'nohora forero-ramirez'=>TRUE,'francisco herrera'=>TRUE,'andrea franco'=>TRUE,'juan pablo franco'=>TRUE,'cristian camilo frasser'=>TRUE,'miguel fuentes'=>TRUE,'ben fung'=>TRUE,'celina gaitan-maldonado'=>TRUE,'jorge e. galan'=>TRUE,'jorge galan camacho'=>TRUE,'juan galvis'=>TRUE,'juan camilo galvis ciro'=>TRUE,'jose r. gamarra'=>TRUE,'michel janna gandur'=>TRUE,'pablo garay'=>TRUE,'andres garcia'=>TRUE,'jorge garcia'=>TRUE,'andres j. garcia-bernal'=>TRUE,'nidia garcia bohorquez'=>TRUE,'julian david garcia-pulgarin'=>TRUE,'gelver garcia santamaria'=>TRUE,'andres felipe garcia-suaza'=>TRUE,'santiago garcia-verdu'=>TRUE,'daira garrido'=>TRUE,'sergio h. garrido-mejia'=>TRUE,'alejandro gaviria'=>TRUE,'xavier gine'=>TRUE,'monica giulietti'=>TRUE,'jose gomez'=>TRUE,'alberto gomez'=>TRUE,'carolina gomez'=>TRUE,'miguel angel gomez'=>TRUE,'miguel ignacio gomez'=>TRUE,'monica alexandra gomez'=>TRUE,'wilman gomez'=>TRUE,'javier gomez restrepo'=>TRUE,'sebastian gomez barrero'=>TRUE,'karen juliet gomez-gonzalez'=>TRUE,'santiago gomez-malagon'=>TRUE,'monica sofia gomez-salcedo'=>TRUE,'mario alejandro gonzalez'=>TRUE,'alejandra gonzalez'=>TRUE,'andres gonzalez'=>TRUE,'bernardo gonzalez'=>TRUE,'camilo gonzalez'=>TRUE,'cristina gonzalez'=>TRUE,'eliana gonzalez'=>TRUE,'hernando gonzalez'=>TRUE,'angela gonzalez arbelaez'=>TRUE,'carlos giovanni gonzalez espitia'=>TRUE,'juanita gonzalez uribe'=>TRUE,'penny gordon-larsen'=>TRUE,'anderson grajales'=>TRUE,'joan camilo granados castro'=>TRUE,'catalina granda'=>TRUE,'fernando grosz'=>TRUE,'arlen guarin'=>TRUE,'david guilkey'=>TRUE,'dominique guillaume'=>TRUE,'javier gutierrez rueda'=>TRUE,'l. guzman-vargas'=>TRUE,'eduardo a. haddad'=>TRUE,'gustavo hernandez'=>TRUE,'camilo hernandez'=>TRUE,'juan nicolas hernandez'=>TRUE,'lola hernandez'=>TRUE,'mauricio a. hernandez'=>TRUE,'rafael hernandez'=>TRUE,'monica hernandez'=>TRUE,'antonio hernandez-gamarra'=>TRUE,'juan manuel hernandez herrera'=>TRUE,'german h. hernandez leal'=>TRUE,'juan d. hernandez-leal'=>TRUE,'pedro oswaldo hernandez s.'=>TRUE,'magaly herrera'=>TRUE,'paula herrera'=>TRUE,'santiago herrera a.'=>TRUE,'geoffrey j. d. hewings'=>TRUE,'jorge hirs-garzon'=>TRUE,'marc hofstetter'=>TRUE,'dylan hogg'=>TRUE,'mark j. holmes'=>TRUE,'carlos huertas-campos'=>TRUE,'angela maria hurtado'=>TRUE,'kim p. huynh'=>TRUE,'armando ibarra'=>TRUE,'idrobo nicolas'=>TRUE,'isaac guerrero rincon'=>TRUE,'daniel andres jaimes cardenas'=>TRUE,'munir a. jalil b.'=>TRUE,'diego jara'=>TRUE,'carlos felipe jaramillo'=>TRUE,'jaime jaramillo'=>TRUE,'roberto luis jaramillo'=>TRUE,'juliana jaramillo-echeverri'=>TRUE,'andres eduardo jimenez-gomez'=>TRUE,'jorge ramos'=>TRUE,'alvaro jose pinzon'=>TRUE,'roberto junguito'=>TRUE,'salomon kalmanovitz'=>TRUE,'herman kamil'=>TRUE,'nicholas m. kiefer'=>TRUE,'geun-young kim'=>TRUE,'floor e. w. knoote'=>TRUE,'guido m. kuersteiner'=>TRUE,'maurice kugler'=>TRUE,'yasin kursat onder'=>TRUE,'ali m. kutan'=>TRUE,'cecilia lagorio'=>TRUE,'andres langebaek'=>TRUE,'juan mario laserna'=>TRUE,'mariana laverde'=>TRUE,'alyssa lee'=>TRUE,'daeyup lee'=>TRUE,'pedro felipe lega'=>TRUE,'jose leibovich'=>TRUE,'karen juliet leiton rodriguez'=>TRUE,'john jairo leon'=>TRUE,'bernardo leyva-uribe'=>TRUE,'xiaoquan liu'=>TRUE,'ruben albeiro loaiza maya'=>TRUE,'ana maria loboguerrero'=>TRUE,'wing lon ng'=>TRUE,'harold londoño'=>TRUE,'jacinto londoño'=>TRUE,'sebastian londoño'=>TRUE,'david lopez'=>TRUE,'adriana lopez'=>TRUE,'alejandro lopez'=>TRUE,'hugo lopez castaño'=>TRUE,'ana maria lopez soto'=>TRUE,'johanna lopez velandia'=>TRUE,'roderick luna'=>TRUE,'pablo alejandro macri'=>TRUE,'grupo macroeconomia 2006'=>TRUE,'lavan mahadeva'=>TRUE,'felipe marin'=>TRUE,'margarita marin'=>TRUE,'ricardo mariño'=>TRUE,'daniel mariño-ustacara'=>TRUE,'juan d. martin'=>TRUE,'clara patricia martin'=>TRUE,'andres felipe martinez'=>TRUE,'gloria cecilia martinez'=>TRUE,'ivonne martinez'=>TRUE,'jaime albeiro martinez'=>TRUE,'jimmy martinez'=>TRUE,'maria adelaida martinez'=>TRUE,'oscar martinez'=>TRUE,'oscar martinez a.'=>TRUE,'jorge martinez t.'=>TRUE,'alejandro medina'=>TRUE,'carlos medina'=>TRUE,'daniel medina'=>TRUE,'costas meghir'=>TRUE,'carolina mejia'=>TRUE,'daniel mejia'=>TRUE,'luis fernando mejia'=>TRUE,'cristina mendana'=>TRUE,'omar mendoza'=>TRUE,'silvia juliana mera'=>TRUE,'m.v. migueles'=>TRUE,'milas costas'=>TRUE,'martha misas'=>TRUE,'linda mondragon'=>TRUE,'ingrid monroy'=>TRUE,'viviana monroy'=>TRUE,'emma monsalve'=>TRUE,'armando montenegro'=>TRUE,'paola montenegro'=>TRUE,'humberto mora'=>TRUE,'tatiana a. mora-arbelaez'=>TRUE,'miguel morales'=>TRUE,'patricia morales'=>TRUE,'camilo morales j.'=>TRUE,'paola morales acevedo'=>TRUE,'miguel angel morales mosquera'=>TRUE,'jose fernando moreno-gutierrez'=>TRUE,'lina marcela moyano'=>TRUE,'santiago muñoz'=>TRUE,'cesar muñoz c.'=>TRUE,'andres murcia'=>TRUE,'fabio h. nieto'=>TRUE,'mario nigrinis ospina'=>TRUE,'patrick nolen'=>TRUE,'hector nuñez'=>TRUE,'jairo nuñez-mendez'=>TRUE,'oskar andres nupia'=>TRUE,'nataly obando'=>TRUE,'segio ocampo'=>TRUE,'sergio ocampo diaz'=>TRUE,'hector ochoa'=>TRUE,'sergio olarte'=>TRUE,'hugo oliveros'=>TRUE,'daniel ordoñez-callamand'=>TRUE,'shmuel oren'=>TRUE,'antonio orozco'=>TRUE,'antonio jose orozco-gallo'=>TRUE,'ines paola orozco'=>TRUE,'sofia ortega-tineo'=>TRUE,'maria camila ortiz'=>TRUE,'carlos humberto ortiz'=>TRUE,'daniel osorio'=>TRUE,'poldy osorio'=>TRUE,'walter osorio r.'=>TRUE,'enrique ospina'=>TRUE,'monica ospina'=>TRUE,'sandra patricia ospina'=>TRUE,'jesus otero'=>TRUE,'andres pabon'=>TRUE,'angelica pachon'=>TRUE,'maria del mar palau'=>TRUE,'blanca monica-panqueva'=>TRUE,'anthony papavasiliou'=>TRUE,'joaquin e. paredes vega'=>TRUE,'freddy felipe parra'=>TRUE,'julieth parra'=>TRUE,'juan carlos parra alvarez'=>TRUE,'ligia marcela parrado-galvis'=>TRUE,'sergio parra ulloa'=>TRUE,'zeinab partow'=>TRUE,'carlos ignacio patiño'=>TRUE,'hilde patron'=>TRUE,'aura c. pedraza avella'=>TRUE,'alejandro pelaez'=>TRUE,'karen penagos q.'=>TRUE,'ximena peña'=>TRUE,'jhonatan perez'=>TRUE,'julian perez'=>TRUE,'julian perez-amaya'=>TRUE,'david perez-reyna'=>TRUE,'jhonatan perez villalobos'=>TRUE,'f.s. perobelli'=>TRUE,'peter sarlin'=>TRUE,'david c. phillips'=>TRUE,'andres pinchao-rosero'=>TRUE,'pablo pincheira'=>TRUE,'fernando pineda'=>TRUE,'gabriel piraquive'=>TRUE,'javier eliecer pirateque niño'=>TRUE,'lewis enrique polo'=>TRUE,'adriana ponton'=>TRUE,'carlos esteban posada'=>TRUE,'juan david prada-sarmiento'=>TRUE,'jose david pulido'=>TRUE,'jose pulido'=>TRUE,'carolina pulido gonzalez'=>TRUE,'rafael puyana martinez-villaba'=>TRUE,'pablo querubin'=>TRUE,'carlos andres quicazan moreno'=>TRUE,'pastor enrique quintero'=>TRUE,'paola quintero puentes'=>TRUE,'manuel ramirez'=>TRUE,'alvaro alberto ramirez'=>TRUE,'carolina ramirez'=>TRUE,'juan mauricio ramirez'=>TRUE,'juan m.ramirez c.'=>TRUE,'natalia ramirez bustamante'=>TRUE,'andres ramirez hassan'=>TRUE,'lina ma. ramirez-villegas'=>TRUE,'juan sebastian rassa robayo'=>TRUE,'angelica rengifo gomez'=>TRUE,'luc renneboog'=>TRUE,'gonzalo restrepo'=>TRUE,'jorge e. restrepo'=>TRUE,'juan camilo restrepo'=>TRUE,'sergio restrepo angel'=>TRUE,'paulina restrepo echavarria'=>TRUE,'alejandro reveiz herault'=>TRUE,'catalina rey guerra'=>TRUE,'ruth reyes nidia'=>TRUE,'catalina rey-guerra'=>TRUE,'remberto rhenals'=>TRUE,'alvaro j. riascos'=>TRUE,'ana maria rios'=>TRUE,'maria ripoll'=>TRUE,'marla ripoll'=>TRUE,'monica roa'=>TRUE,'carlos a. rocha'=>TRUE,'weslem rodrigues faria'=>TRUE,'mauricio rodriguez'=>TRUE,'miguel a. rodriguez'=>TRUE,'diego rodriguez'=>TRUE,'angela milena rojas'=>TRUE,'diego rojas'=>TRUE,'luis eduardo rojas'=>TRUE,'sebastian rojas'=>TRUE,'andrea rojas a.'=>TRUE,'juan sebastian rojas-bohorquez'=>TRUE,'carmen astrid romero'=>TRUE,'maria fernanda rosales'=>TRUE,'peter rowland'=>TRUE,'vicente royuela'=>TRUE,'sandra rozo'=>TRUE,'eliana carolina rubiano'=>TRUE,'orlando rubio m.'=>TRUE,'leonardo rueda'=>TRUE,'fabio rueda devivero'=>TRUE,'jorge leonardo rueda gil'=>TRUE,'cristhian ruiz cardozo'=>TRUE,'nidia ruth reyes'=>TRUE,'agustin saade'=>TRUE,'t. l. saaty'=>TRUE,'juan esteban saavedra'=>TRUE,'luz amparo saavedra'=>TRUE,'leonard sabetti'=>TRUE,'dagoberto saboya'=>TRUE,'andres salamanca'=>TRUE,'david m. salamanca rojas'=>TRUE,'mauricio salazar'=>TRUE,'irene salazar'=>TRUE,'jose mauricio salazar saenz'=>TRUE,'elioth mirsha sanabria-buenaventura'=>TRUE,'daniela sanchez'=>TRUE,'katherine sanchez'=>TRUE,'paulo mauricio sanchez beltran'=>TRUE,'bernardo saray ricardo'=>TRUE,'eduardo sarmiento'=>TRUE,'miguel sarmiento'=>TRUE,'viviana sarmiento'=>TRUE,'miguel sarmiento paipilla'=>TRUE,'natalia serna'=>TRUE,'shirly marrugo llorente'=>TRUE,'patricia siado c.'=>TRUE,'natalia sicard'=>TRUE,'lya paola sierra suarez'=>TRUE,'alejandro silva'=>TRUE,'armando silva'=>TRUE,'jorge edgar silva'=>TRUE,'daphne skandalis'=>TRUE,'roberto steiner'=>TRUE,'marc st-pierre'=>TRUE,'gerald stuber'=>TRUE,'gustavo suarez'=>TRUE,'nicolas f. suarez-ariza'=>TRUE,'felipe suarez parra'=>TRUE,'rodrigo suescun m.'=>TRUE,'cesar e. tamayo'=>TRUE,'kadir tanyeri'=>TRUE,'johanna tautiva'=>TRUE,'gerencia tecnica'=>TRUE,'santiago tellez'=>TRUE,'juana patricia tellez-corredor'=>TRUE,'fernando tenjo galarza'=>TRUE,'timo terasvirta'=>TRUE,'h theil'=>TRUE,'evelyn yohana tique calderon'=>TRUE,'carlo tognato'=>TRUE,'jose tolosa buitrago'=>TRUE,'jose luis torres'=>TRUE,'andres trejos'=>TRUE,'edgar trujillo c.'=>TRUE,'james tybout'=>TRUE,'camila uribe'=>TRUE,'jose dario uribe'=>TRUE,'jorge mario uribe gil'=>TRUE,'joaquin urrego'=>TRUE,'miguel urrutia'=>TRUE,'miguel urrutia montoya'=>TRUE,'ferney h. valencia'=>TRUE,'gonzalo valencia'=>TRUE,'hernan vallejo'=>TRUE,'cesar vallejo mejia'=>TRUE,'carlos varela'=>TRUE,'juan manuel vargas'=>TRUE,'l. g. vargas'=>TRUE,'laura vargas'=>TRUE,'varya taylor'=>TRUE,'diego vasquez'=>TRUE,'diego mauricio vasquez'=>TRUE,'javier yabrudy vega'=>TRUE,'margarita vega'=>TRUE,'daniel vela'=>TRUE,'daniel eduardo velandia'=>TRUE,'andres m. velasco'=>TRUE,'andres velasco'=>TRUE,'carlos eduardo velez'=>TRUE,'tatiana venegas'=>TRUE,'pavel vidal alejandro'=>TRUE,'juan miguel villa'=>TRUE,'martha lucia villa'=>TRUE,'consuelo villalba torres'=>TRUE,'leonardo villar gomez'=>TRUE,'juan g. villegas'=>TRUE,'joaquin viloria de la hoz'=>TRUE,'francisco vivas'=>TRUE,'nancy eugenia zamudio gomez'=>TRUE,'daniel r. zapata-sanabria'=>TRUE,'juan pablo zarate perdomo'=>TRUE,'camilo zea'=>TRUE,'miguel zerecero'=>TRUE,'george r. zodrow'=>TRUE,'igor esteban zuccardi huertas'=>TRUE,'hernando zuleta'=>TRUE,'banco de la republica'=>TRUE,'centro de estudios regionales ceer'=>TRUE,'departamento de fiduciaria y valores'=>TRUE,'finagro'=>TRUE,'gerencia de riesgo asobancaria cifin'=>TRUE,'ministerio agricultura'=>TRUE,'greco'=>TRUE,'adriaan ten kate'=>TRUE,'adrian de leon'=>TRUE,'adriana ferrufino echeverri'=>TRUE,'alberto calderon zuleta'=>TRUE,'alberto ernesto isgut'=>TRUE,'alberto torres'=>TRUE,'alejandro becerra'=>TRUE,'alejandro diaz de leon'=>TRUE,'alejandro quijada'=>TRUE,'alejandro torres'=>TRUE,'alessio ciarlone'=>TRUE,'alexander tobon'=>TRUE,'alexandros vardoulakis'=>TRUE,'alvaro monge'=>TRUE,'alvaro riascos'=>TRUE,'ana maria olaya'=>TRUE,'andrea colabella'=>TRUE,'andres acosta'=>TRUE,'andres escobar arango'=>TRUE,'andres felipe londoño'=>TRUE,'andres giraldo'=>TRUE,'andres mora'=>TRUE,'andres pardo amezquita'=>TRUE,'angela redish'=>TRUE,'anil kashyap'=>TRUE,'armando baqueiro'=>TRUE,'bernardo leon'=>TRUE,'bernardo vargas gibsone'=>TRUE,'carl e walsh'=>TRUE,'carlos a. vegh'=>TRUE,'carlos alberto rodriguez lopez'=>TRUE,'carlos alberto velasquez'=>TRUE,'carlos andres brando'=>TRUE,'carlos eduardo acosta'=>TRUE,'carlos f. prada'=>TRUE,'carlos felipe prada'=>TRUE,'carlos iglesias'=>TRUE,'carlos urzua'=>TRUE,'carmen helena botero arboleda'=>TRUE,'carmen reinhart'=>TRUE,'carolina osorio'=>TRUE,'carolina renteria rodriguez'=>TRUE,'carolina roman ramos'=>TRUE,'catalina delgado'=>TRUE,'catalina gutierrez sourdis'=>TRUE,'charle augusto londoño'=>TRUE,'christian camilo gomez'=>TRUE,'claudio r karl'=>TRUE,'cristina martinez'=>TRUE,'daniel castellanos'=>TRUE,'daniel riera'=>TRUE,'dario maldonado'=>TRUE,'david e yuravlivker'=>TRUE,'david mayes'=>TRUE,'dennis sanchez'=>TRUE,'diana marcela guiza'=>TRUE,'diana marcela jimenez'=>TRUE,'diego amadora'=>TRUE,'diego dueñas'=>TRUE,'diego fernando tellez'=>TRUE,'diego urbina'=>TRUE,'diego winkelried'=>TRUE,'dimitrios tsomocos'=>TRUE,'dong guo'=>TRUE,'dornbusch rudiger'=>TRUE,'eddie gerba'=>TRUE,'edgar demetrio tovar'=>TRUE,'edgar villa'=>TRUE,'eduardo bolaños'=>TRUE,'eduardo lora torres'=>TRUE,'egberto alexander riveros'=>TRUE,'emma osorio'=>TRUE,'enrique alberola'=>TRUE,'enrique g. mendoza'=>TRUE,'erika raquel badillo'=>TRUE,'ernesto labra'=>TRUE,'fabian camilo gomez'=>TRUE,'fabian stumph carolyn'=>TRUE,'fernando montes negret'=>TRUE,'fischer stanley'=>TRUE,'francesco caselli'=>TRUE,'francisco jose ortega acosta'=>TRUE,'frank rock gunter'=>TRUE,'george mccandless'=>TRUE,'gil bufman'=>TRUE,'gilberto arango londoño'=>TRUE,'giovanni andres hernandez'=>TRUE,'gloria amparo alonso masmela'=>TRUE,'guillermo a. calvo'=>TRUE,'guillermo david hincapie'=>TRUE,'guillermo mondiano'=>TRUE,'guillermo sylvia'=>TRUE,'guillermo vuletin'=>TRUE,'gustavo adolfo gomez'=>TRUE,'gustavo alberto sanchez'=>TRUE,'gustavo andres suarez roa'=>TRUE,'harvy vivas'=>TRUE,'helena villamizar garcia-herreros'=>TRUE,'henderson vernon'=>TRUE,'hernan botero'=>TRUE,'hernando jose gomez restrepo'=>TRUE,'humberto mora alvarez'=>TRUE,'hwa erh-cheng'=>TRUE,'irving joel llamosas'=>TRUE,'isaac dyner'=>TRUE,'isabel alvarez'=>TRUE,'ismael rodriguez'=>TRUE,'israel fainboim yaker'=>TRUE,'ivonne rocio leon'=>TRUE,'jaime ramirez'=>TRUE,'jaime tenjo'=>TRUE,'james r tybout'=>TRUE,'jan zizek'=>TRUE,'javier armando pineda'=>TRUE,'javier fernandez riva'=>TRUE,'javier perez'=>TRUE,'jesus maria godoy'=>TRUE,'jhonny moncada'=>TRUE,'jimmy melo'=>TRUE,'johanna gaitan'=>TRUE,'john jairo prado'=>TRUE,'john t. cuddington'=>TRUE,'jonathan scott davis'=>TRUE,'jorge andres velez ospina'=>TRUE,'jorge barrientos marin'=>TRUE,'jorge david quintero'=>TRUE,'jorge e. espitia'=>TRUE,'jorge enrique restrepo londoño'=>TRUE,'jorge lotero'=>TRUE,'jose antonio ocampo gaviria'=>TRUE,'jose de gregorio'=>TRUE,'jose ignacio uribe'=>TRUE,'jose mauricio gil leon'=>TRUE,'joseph p joyce'=>TRUE,'juan antonio rock'=>TRUE,'juan c duque'=>TRUE,'juan carlos guataqui roa'=>TRUE,'juan carlos jaramillo franco'=>TRUE,'juan carlos muñoz'=>TRUE,'juan carlos vargas berdugo'=>TRUE,'juan david duran'=>TRUE,'juan david prada'=>TRUE,'juan esteban velez'=>TRUE,'juan guillermo serna valencia'=>TRUE,'juan hernandez'=>TRUE,'juan ricardo ortega'=>TRUE,'julian villamil'=>TRUE,'julio cesar angel mejia'=>TRUE,'karel jansen'=>TRUE,'karina lujan'=>TRUE,'katherine cartagena'=>TRUE,'kongsamut piyabha'=>TRUE,'laura ardila rueda'=>TRUE,'laurence ball'=>TRUE,'leonardo gambacorta'=>TRUE,'leonardo leiderman'=>TRUE,'leonardo rosero hurtado'=>TRUE,'leonardo santana'=>TRUE,'lia guterman bromberg'=>TRUE,'lilian carol bohorquez'=>TRUE,'liliana olarte'=>TRUE,'lina marcela osorio'=>TRUE,'lina maria sanchez'=>TRUE,'lina maria vasquez'=>TRUE,'linda kamas'=>TRUE,'lorena silvani de moreno'=>TRUE,'luigi pascali'=>TRUE,'luis edgar basto'=>TRUE,'luis enrique pedauga'=>TRUE,'luis felipe jaime couott'=>TRUE,'luis fernando gamboa'=>TRUE,'luis guillermo becerra'=>TRUE,'luis jorge garay salamanca'=>TRUE,'luis lorente sanchez-bravo'=>TRUE,'luis mario lopez'=>TRUE,'luisa fernanda gutierrez'=>TRUE,'m. cherif'=>TRUE,'manuel fernandez sierra'=>TRUE,'manuel gilberto rosas'=>TRUE,'marcello estevao'=>TRUE,'marcelo sanchez'=>TRUE,'marco a rodriguez waldo'=>TRUE,'marco lombardi'=>TRUE,'maria claudia correa ordoñez'=>TRUE,'maria ines agudelo valencia'=>TRUE,'maria isabel garcia castro'=>TRUE,'maria teresa valderrama andrade'=>TRUE,'mario i. blejer'=>TRUE,'mark j roberts'=>TRUE,'martha lee wynne'=>TRUE,'martin alberto rodriguez brindis'=>TRUE,'martin maurer'=>TRUE,'martin uribe'=>TRUE,'matti viren'=>TRUE,'mauricio arango'=>TRUE,'mauricio carrizosa serrano'=>TRUE,'mauricio hernandez'=>TRUE,'mauricio olivera g.'=>TRUE,'mauricio ruiz'=>TRUE,'mayshar joram'=>TRUE,'michael m. hutchison'=>TRUE,'miguel gomez'=>TRUE,'monica enciso'=>TRUE,'natalia salazar'=>TRUE,'natalia salazar ferro'=>TRUE,'nataly rendon gonzalez'=>TRUE,'neeman zvika'=>TRUE,'nestor rubiano'=>TRUE,'olga lucia acosta navarro'=>TRUE,'olga marcela namen'=>TRUE,'oliver pardo'=>TRUE,'olver luis bernal barreto'=>TRUE,'omer moav'=>TRUE,'orlando chipatecua'=>TRUE,'oscar valencia'=>TRUE,'osmar leandro loaiza'=>TRUE,'pablo daniel monterubbianesi'=>TRUE,'pablo martin aceña'=>TRUE,'pang gaobo'=>TRUE,'pardo oliver'=>TRUE,'patricia arciniegas bonilla'=>TRUE,'paul de grauwe'=>TRUE,'pedro luis rodriguez peralta'=>TRUE,'peter claeys'=>TRUE,'philip r lane'=>TRUE,'pierre siklos'=>TRUE,'raquel bernal salazar'=>TRUE,'raquel llorente'=>TRUE,'ricardo candelo cardenas'=>TRUE,'ricardo jose salas diaz'=>TRUE,'rob rennhack'=>TRUE,'roberto junguito bonnet'=>TRUE,'rocio gondo'=>TRUE,'rodrigo suescun melo'=>TRUE,'rodrigo taborda'=>TRUE,'rolando gonzales'=>TRUE,'romilio labra'=>TRUE,'roque b fernandez'=>TRUE,'sandy dall’erba'=>TRUE,'santiago alberico'=>TRUE,'santiago arango'=>TRUE,'santiago villegas salazar'=>TRUE,'sebastian edwards'=>TRUE,'sergio j rey'=>TRUE,'sergio ocampo'=>TRUE,'sergio parra cely'=>TRUE,'stefano tijerina'=>TRUE,'stella cordoba de gonzalez'=>TRUE,'stephanie schmitt'=>TRUE,'sylvia beatriz guillermo peon'=>TRUE,'tanka beata'=>TRUE,'thomas goda'=>TRUE,'thomas m fullerton'=>TRUE,'vanessa galeano'=>TRUE,'veronica bayangos'=>TRUE,'victor alexander diaz'=>TRUE,'vincent reinhart'=>TRUE,'vincenzo quadrini'=>TRUE,'vittorio corbo'=>TRUE,'volker nitsch'=>TRUE,'vonnak balazs'=>TRUE,'watson lakhovsky nadine'=>TRUE,'william easterly'=>TRUE,'wilman arturo gomez muñoz'=>TRUE,'yeinni andrea patiño'=>TRUE,);
  public function __construct($arguments) {
    parent::__construct($arguments);
    $fields = array(
      'titulo' => 'Título de la Publicación',
      'tipo' => 'Tipo de publicacion',
      'concepto' => 'Concepto',
      'editorial' => 'Editorial',
      'palabras_clave' => 'field_palabras_clave',
      'jel' => 'JEL',
      'page' => 'Páginas',
      'descripcion' => 'Descripción',
      'dia' => 'Día',
      'mes' => 'Mes',
      'anio' => 'Anio',
      'numero' => 'Número',
      'volumen' => 'Volumen',
      'url_repec' => 'Url Repec',
      'url' => 'Url',
      'autor' => 'Autor',
      'coautor1' => 'coautor1',
      'coautor2' => 'coautor2',
      'coautor3' => 'coautor3',
      'coautor4' => 'coautor4',
      'coautor5' => 'coautor5',
      'bautor' => 'B Autor',
      'bcoautor1' => 'B coautor1',
      'bcoautor2' => 'B coautor2',
      'bcoautor3' => 'B coautor3',
      'bcoautor4' => 'B coautor4',
      'bcoautor5' => 'B coautor5',
      'pid' => 'pid',
    );
    $this->description = t('Json de publicaciones investigadores');
    $this->source =
      new MigrateSourceJSON(
        format_json('public://migration/pubs-1.json'),
        'pid',
        $fields
      )
    ;
    $this->destination = new MigrateDestinationNode('publication');
    $this->map =
      new MigrateSQLMap(
        $this->machineName,
        array(
          'pid' => array(
            'type' => 'varchar',
            'length' => 255,
            'description' => 'Contenido ID.',
            'not null' => TRUE
          )
        ),
        MigrateDestinationNode::getKeySchema()
      )
    ;
    $this->addFieldMapping('title', 'titulo');
    $this
      ->addFieldMapping('field_pub_type', 'tipo')
      ->callbacks(array($this, 'convertPublicationType'))
    ;
    $this->addFieldMapping('field_pub_serie', 'serie');
    $this->addFieldMapping('field_editorial', 'editorial');
    $this
      ->addFieldMapping('field_publication_tags', 'palabras_clave')
      ->separator(',')
    ;
    $this
      ->addFieldMapping('field_publication_tags:create_term')
      ->defaultValue(TRUE)
    ;
    $this->addFieldMapping('field_jel', 'jel')->separator(',');
    $this->addFieldMapping('field_page', 'page');
    $this->addFieldMapping('field_date', 'fecha');
    $this->addFieldMapping('field_publication_year', 'anio');
    $this->addFieldMapping('field_number', 'numero');
    $this->addFieldMapping('field_volumen', 'volumen');
    $this->addFieldMapping('field_url', 'url_portal');
    $this->addFieldMapping('field_role_within_publication', 'rol_publicacion');
    $this
      ->addFieldMapping('field_role_within_publication:source_type')
      ->defaultValue('tid')
    ;
    $this->addFieldMapping('field_concept', 'concepto');
    $this
      ->addFieldMapping('field_concept:source_type')
      ->defaultValue('target_id')
    ;
    $this->addFieldMapping('field_main_author_reference', 'autor_principal');
    $this
      ->addFieldMapping('field_other_co_authors', 'autores_externos')
      ->separator('|')
    ;
    $this
      ->addFieldMapping('field_other_co_authors:create_term')
      ->defaultValue(TRUE)
    ;
    $this->addFieldMapping('field_review')->defaultValue('revisado');
    $this->addFieldMapping('field_pid', 'pid');
    $this->addFieldMapping('field_estado_publicaci_n')->defaultValue(TRUE);
    $this->addFieldMapping('status', 'status')->defaultValue(1);
  }

  private static function cleanKey($key) {
    $key = trim($key);
    $key = mb_ereg_replace('\s+', ' ', $key);
    $key = mb_strtolower($key);
    $key = mb_ereg_replace('[áàäâã]', 'a', $key);
    $key = mb_ereg_replace('[éèëê]', 'e', $key);
    $key = mb_ereg_replace('[íìïî]', 'i', $key);
    $key = mb_ereg_replace('[óòöôõ]', 'o', $key);
    $key = mb_ereg_replace('[úùüû]', 'u', $key);
    return $key;
  }

  protected function convertPublicationType($value) {
    switch (strtolower($value)) {
      case 'documentos de trabajo':
        return 2951;
      case 'articulo':
        return 201;
      case 'libro':
        return 206;
      default:
        return $value;
    }
  }

  public function prepareRow($row) {
    if (parent::prepareRow($row) === FALSE) {
      return FALSE;
    }
    $row->uid = 1;
    $mes_normalizado = _publication_obtener_mes_numerico($row->mes);
    $dia_normalizado = isset($row->dias) ? $row->dias : 1;
    $fecha = $mes_normalizado .'/'. $dia_normalizado .'/' . $row->anio;
    $row->fecha = strtotime($fecha);
    $row->url_portal = (!empty($row->url_repec)) ? $row->url_repec : $row->url;
    $row->rol_publicacion = 219;
    //$row->concepto = _publication_obtener_nid_concepto($row->concepto);
    $row->concepto = 10876;
    // if ($row->tipo == 'articulo') {
    //   if ($row->anio >= 2008) {
    //     $row->concepto = 4449;
    //   }
    //   elseif ($row->anio >= 2004 && $row->anio < 2008) {
    //     $row->concepto = 4450;
    //   }
    //   else {
    //    $row->concepto = 4450;
    //   }
    // }
    // elseif ($row->tipo == 'libro') {
    //   $row->concepto = 4442;
    // }
    // elseif ($row->tipo == 'documento de trabajo') {
    //   $row->concepto = 3829;
    // }
    $autores_inicial = array(
      array('nombre' => $row->autor),//, 'banco' => $row->bautor,),
      array('nombre' => $row->coautor1),//, 'banco' => $row->bcoautor1,),
      array('nombre' => $row->coautor2),//, 'banco' => $row->bcoautor2,),
      array('nombre' => $row->coautor3),//, 'banco' => $row->bcoautor3,),
      array('nombre' => $row->coautor4),//, 'banco' => $row->bcoautor4,),
      array('nombre' => (isset($row->coautor5) ? $row->coautor5 : '')),//, 'banco' => $row->bcoautor5,),
    );
    $flag_autor = TRUE;
    $autores_banco = array();
    $autores_externo = array();
    foreach ($autores_inicial as $autor) {
      if ($autor['nombre']) {
        $autor_limpio = self::cleanKey($autor['nombre']);
        // if ($autor['banco'] == 'si') {
        if (isset(self::$internos[$autor_limpio])) {
          $uid = _publication_obtener_autor(self::$internos[$autor_limpio]);
          if ($uid) {
            $item = array('uid' => $uid, 'rid' => 219);
            if ($flag_autor) {
              $item['main'] = TRUE;
              $flag_autor = FALSE;
            }
            $autores_banco[] = $item;
          }
          else {
            dpm(
              '"' .
              $autor['nombre'] .
              '" no está en el sistema. En "' .
              $row->titulo .
              '"'
            );
          }
        }
        elseif (isset(self::$externos[$autor_limpio])) {
          if ($flag_autor) {
            $row->autor_principal = $autor['nombre'];
            $flag_autor = FALSE;
          }
          else {
            $autores_externo[] = $autor['nombre'];
          }
        }
        else {
          dpm(
            '"' .
            $autor['nombre'] .
            '" no está en la pestaña de usuarios. En "' .
            $row->titulo .
            '"'
          );
        }
      }
    }
    if (!empty($autores_externo)) {
      $row->autores_externos = implode('|', $autores_externo);
    }
    else {
      $row->autores_externos = '';
    }
    $row->autores_banco = $autores_banco;
  }

  public function prepare(stdClass $entity, stdClass $current_row) {
    // $tids = _get_concept_category($current_row->tipo_publicacion);
    // //$index = _get_index_nid($current_row->index);
    // //$entity->field_concept_category['und'] = $tids;
    // if (!empty($index)) {
    //   $entity->field_index['und'][]['target_id'] = $index;
    //   dpm($entity);
    //   //dpm();
    // }
  }

  /*
  * The Migration class complete() method is analogous to prepare(), but is called immediately after the complete
  * destination object is saved.
  */
  public function complete($entity, stdClass $row) {
    $node = $entity;
    if (!empty($row->autores_banco)) {
      _publication_create_co_authors_banco($node->nid, $row->autores_banco, TRUE);
    }
    // set state publication to approved
    // $node->field_estado_publicaci_n['und'][0]['value'] = 3;
    $node->status = 1;
    node_save($node);
  }
}
