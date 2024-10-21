function person(name, age){
    this.name = name
    this.age = age
}

john = person("john", "21")

console.log(john.name)