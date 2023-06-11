const typer = document.getElementById('typewriter');
typer.innerText = '';

document.onkeyup =  async (e)=>{
    if (e.ctrlKey || e.altKey || e.metaKey) return;
    if (["Shift","Control","Alt","Meta","OS","Tab", "Enter","Escape"].includes(e.key)) return;
    if (e.key == 'Backspace') {
        typer.textContent = typer.textContent.substring(0, typer.innerText.length - 1);
        document.getElementById('prompt').innerHTML = highlight(typer.textContent, document.getElementById('prompt').dataset.prompt);
        return;
    }
    if (e.key == ' ') {
        typer.textContent += ' ';
    } else {
        typer.textContent += e.key;
    }
    let text = typer.textContent;
    let keyPressed = {
        key: e.key,
        location: e.location,
        when: new Date().getTime(),
        more: e.detail,
    };
    console.log(keyPressed);
    document.getElementById('prompt').innerHTML = highlight(text, document.getElementById('prompt').dataset.prompt);
    
    await fetch('/times', {
        method: 'POST',
        body: JSON.stringify({
            event: keyPressed,
        }),
        headers: {
            'Content-Type': 'application/json'
        }
    }).then(function (response) {
        return response.json();
    })
    
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
            document.getElementById('flag').innerText = data.flag ?? data.status ?? "too slow!";
        });

        typer.onkeyup = null;        
    }
}

function highlight(substr, str) {
    if (!str.startsWith(substr)) return str;
    let index = str.indexOf(substr);
    return "<span class='right'>" + substr + "</span>" + str.substring(index + substr.length);
}