var choice=function(arr) {
    return arr[Math.floor(arr.length * Math.random())];
}

var fixCap=function(string){
    var output = ""
    var inasentence = false
    for (var i of string){
        if (inasentence){
            output+=(i)
            if ('.?!'.indexOf(i)>=0)
            {
            inasentence = false
            }
        }
        else{
            output+=(i.toUpperCase())
            if(" ?!".indexOf(i)==-1){
                inasentence = true
            }
        }
                
    
    }
return output.replace(" i "," I ")
    
}


function genFortune(Data){
    Data=JSON.parse(JSON.stringify(Data));
    var Pattern = choice(Data['Patterns'])

    for(var i=0;i<32;i++){
        var b = true
        for (var j in Data['Parts']){
            if (Pattern.indexOf(j)>-1){
                var part = j
                var x =choice(Data['Parts'][j])
                Pattern = Pattern.replace(j , x)
                if (j.indexOf("duplicate") == -1 )
                {
                     Data['Parts'][j]=  Data['Parts'][j].filter(e => e !== x)

                }
                b=false
            }
        }
        
        for (var j in Data['Macro']){
            if (Pattern.indexOf(j)>-1)
            {
                var Temp = choice(Data['Macro'][j]) 
                Pattern = Pattern.replace(j, choice(Data['Macro'][j]))
                b = false
            }
        }

        if (b){
            break
        }
    }
    return fixCap(Pattern)

}
