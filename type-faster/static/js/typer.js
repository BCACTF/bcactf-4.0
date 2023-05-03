const typer = document.getElementById('typewriter');
typer.value = '';

window.addEventListener('load', function () {
    let time = new Date().getTime();
    fetch('/times', {
        method: 'POST',
        body: JSON.stringify({
            start_time: time
        }),
        headers: {
            'Content-Type': 'application/json'
        }
    }).then(function (response) {
        return response.json();
    }).then(function (data) {
        console.log(data);
    });
});

typer.onkeyup =  async (e)=>{
    let text = e.target.value;
    document.getElementById('prompt').innerHTML = highlight(text, document.getElementById('prompt').dataset.prompt);
    
    if (text.trim() == document.getElementById('prompt').dataset.prompt.trim()) {
        let time = new Date().getTime();
        await fetch('/times', {
            method: 'POST',
            body: JSON.stringify({
                end_time: time
            }),
            headers: {
                'Content-Type': 'application/json'
            }
        }).then(function (response) {
            return response.json();
        }).then(function (data) {
            document.getElementById('flag').innerText = data.flag ?? "too slow!";
        });

        alert('done');
        typer.onkeyup = null;
        
    }
}

function highlight(substr, str) {
    if (!str.includes(substr)) return str;
    let index = str.indexOf(substr);
    return "<span class='right'>" + substr + "</span>" + str.substring(index + substr.length);
}