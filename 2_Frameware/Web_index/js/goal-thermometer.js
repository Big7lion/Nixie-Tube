/**
 * @author Lance Snider - lance@lancesnider.com
*/

//editable vars
var goalAmount = 125;//how much are you trying to get
//var currentAmount = 85;//how much do you currently have (if you want to define in js, not html)
var lastAmount = 0.0;
var animationTime = 3000;//in milliseconds
var numberPrefix = "";//what comes before the number (set to "" if no prefix)
var numberSuffix = "℃";//what goes after the number
var tickMarkSegementCount = 6;//each segement adds 40px to the height
var widthOfNumbers = 50;//the width in px of the numbers on the left

//standard resolution images
var glassTopImg = "images/thermometer/glassTop.png";
var glassBodyImg = "images/thermometer/glassBody.png";
var redVerticalImg = "images/thermometer/redVertical.png";
var tooltipFGImg = "images/thermometer/tickShine.png";
var glassBottomImg = "images/thermometer/glassBottom.png";
var tootipPointImg = "images/thermometer/tooltipPoint.png";
var tooltipMiddleImg = "images/thermometer/tooltipMiddle.png";
var tooltipButtImg = "images/thermometer/tooltipButt.png";

//high res images
var glassTopImg2x = "images/thermometer/glassTop2x.png";
var glassBodyImg2x = "images/thermometer/glassBody2x.png";
var redVerticalImg2x = "images/thermometer/redVertical2x.png";
var tooltipFGImg2x = "images/thermometer/tickShine2x.png";
var glassBottomImg2x = "images/thermometer/glassBottom2x.png";
var tootipPointImg2x = "images/thermometer/tooltipPoint2x.png";
var tooltipMiddleImg2x = "images/thermometer/tooltipMiddle2x.png";
var tooltipButtImg2x = "images/thermometer/tooltipButt2x.png";

/////////////////////////////////////////
// ------ don't edit below here ------ //
/////////////////////////////////////////

var arrayOfImages;
var imgsLoaded = 0;
var tickHeight = 40;
var mercuryHeightEmpty = 0;
var numberStartY = 6;
var thermTopHeight = 13;
var thermBottomHeight = 51;
var tooltipOffset = 15; 
var heightOfBody;
var mercuryId;
var tooltipId;
var resolution2x = false;

//start once the page is loaded
$( document ).ready(function() {
	determineImageSet();
});

//this checks if it's the high or normal resolution images
function determineImageSet(){
	
	resolution2x = window.devicePixelRatio == 2;//check if resolution2x
	
	if(resolution2x){	
		//switch the regular for 2x res graphics
		glassTopImg = glassTopImg2x;
		glassBodyImg = glassBodyImg2x;
		redVerticalImg = redVerticalImg2x;
		glassBottomImg = glassBottomImg2x;
		tootipPointImg = tootipPointImg2x;
		tooltipButtImg = tooltipButtImg2x;	
	}
	
	createGraphics();
}

//visually create the thermometer
function createGraphics(){
	
	//add the html
	$("#goal-thermometer").html(
		"<div id='therm-numbers'>" + 
		"</div>" + 
		"<div id='therm-graphics'>" + 
			"<img id='therm-top' src='"+glassTopImg+"'></img>" + 
			"<img id='therm-body-bg' src='"+glassBodyImg+"' ></img>" + 
			"<img id='therm-body-mercury' src='"+redVerticalImg+"'></img>" + 
			"<div id='therm-body-fore'></div>" + 
			"<img id='therm-bottom' src='"+glassBottomImg+"'></img>" + 
			"<div id='therm-tooltip'>" + 
				"<img class='tip-left' src='"+tootipPointImg+"'></img>" + 
				"<div class='tip-middle'><p>$0</p></div>" + 
				"<img class='tip-right' src='"+tooltipButtImg+"'></img>" + 
			"</div>" + 
		"</div>"
	);
	
	//preload and add the background images
	$('<img/>').attr('src', tooltipFGImg).load(function(){
		$(this).remove();
		$("#therm-body-fore").css("background-image", "url('"+tooltipFGImg+"')");
		checkIfAllImagesLoaded();
	});
	
	$('<img/>').attr('src', tooltipMiddleImg).load(function(){
		$(this).remove();
		$("#therm-tooltip .tip-middle").css("background-image", "url('" + tooltipMiddleImg + "')");
		checkIfAllImagesLoaded();
	});
	
	//adjust the css
	heightOfBody = tickMarkSegementCount * tickHeight;
	$("#therm-graphics").css("left", widthOfNumbers)
	$("#therm-body-bg").css("height", heightOfBody);
	$("#goal-thermometer").css("height",  heightOfBody + thermTopHeight + thermBottomHeight);
	$("#therm-body-fore").css("height", heightOfBody);
	$("#therm-bottom").css("top", heightOfBody + thermTopHeight);
	mercuryId = $("#therm-body-mercury");
	mercuryId.css("top", heightOfBody + thermTopHeight);
	tooltipId = $("#therm-tooltip");
	tooltipId.css("top", heightOfBody + thermTopHeight - tooltipOffset);
	
	//add the numbers to the left
	numbersDiv = $("#therm-numbers");
	countPerTick = goalAmount/tickMarkSegementCount;
	commaSepCountPerTick = commaSeparateNumber(countPerTick);
	
	//add the number
	for (i = 0; i < tickMarkSegementCount; i++ ) {
		
		yPos = tickHeight * i + numberStartY;
		style = $("<style>.pos" + i + " { top: " + yPos + "px; width:"+widthOfNumbers+"px }</style>");
		$("html > head").append(style);
		dollarText = commaSeparateNumber(goalAmount - countPerTick * i);
		$( numbersDiv ).append( "<div class='therm-number pos" + i + "'>" +dollarText+ "</div>" );
		
	}
	
	//check that the images are loaded before anything
	arrayOfImages = new Array( "#therm-top", "#therm-body-bg", "#therm-body-mercury", "#therm-bottom", ".tip-left", ".tip-right");
	preload(arrayOfImages);
	
};

//check if each image is preloaded
function preload(arrayOfImages) {
	
	for(i=0;i<arrayOfImages.length;i++){
		$(arrayOfImages[i]).load(function() {   checkIfAllImagesLoaded();  });
	}
    
}

//check that all the images are preloaded
function checkIfAllImagesLoaded(){
	imgsLoaded++;
	if(imgsLoaded == arrayOfImages.length+2){
		$("#goal-thermometer").fadeTo(1000, 1, function(){
			animateThermometer();
		});
	}
}


//animate the thermometer
function animateThermometer(){
	
	percentageComplete = currentAmount/goalAmount;
	mercuryHeight = Math.round(heightOfBody * percentageComplete); 
	newMercuryTop = heightOfBody + thermTopHeight - mercuryHeight;
	
	mercuryId.animate({height:mercuryHeight +1, top:newMercuryTop }, animationTime);
	tooltipId.animate({top:newMercuryTop - tooltipOffset}, {duration:animationTime});
	
	tooltipTxt = $("#therm-tooltip .tip-middle p");
	
	//change the tooltip number as it moves
	$({tipAmount: lastAmount}).animate({tipAmount: currentAmount}, {
		duration:animationTime,
		step:function(){
			tooltipTxt.html(commaSeparateNumber(this.tipAmount));
		}
	});
	lastAmount = currentAmount;
}

//format the numbers with $ and commas
function commaSeparateNumber(val){
	//val = Math.ceil(val)
	val = val.toFixed(1);
    while (/(\d+)(\d{3})/.test(val.toString())){
      val = val.toString().replace(/(\d+)(\d{3})/, '$1'+','+'$2');
    }
    return numberPrefix + val + numberSuffix;
}
