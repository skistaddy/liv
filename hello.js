function person(name, age){
    this.name = name
    this.age = age
}

function New(obj){
    res = {}
    for(i in Object.keys(obj)){
        res[obj[Object.keys(obj)[i]]] = obj[Object.keys(obj)[i]]
    }

    return res
}


console.log(john)