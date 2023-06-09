function onCreateOrderClick() {
    let type = document.querySelector(".type").value
    let amount = document.querySelector(".amount").value
    let name = "Bob Brooks"

    let json = JSON.stringify({name:name, types:[type], amounts:[amount]})
    document.cookie = "order="+json
}