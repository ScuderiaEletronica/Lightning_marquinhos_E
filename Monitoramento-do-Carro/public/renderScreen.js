const ref = firebase.database().ref().child('meters')

ref.on('value', function (snap) {
    console.log(snap.val())

    for (const key in snap.val()) {
        const meter = snap.val()[key];
        const meterid = document.querySelector('.' + meter.tag + ' span')
        meterid.innerHTML = meter.value
        if(meter.value >= meter.max || meter.value <= meter.min){
            meterid.classList.add("extremos")
        }
        else{
            meterid.classList.remove("extremos")
        }
    }
})