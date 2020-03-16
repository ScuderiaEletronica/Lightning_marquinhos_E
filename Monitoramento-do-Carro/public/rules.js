const meters_database = {};

(function () {
    
    let meterid = false

    function new_meter(meter) {
        
        var meter_data = {
            name: meter.name,
            value: meter.value,
            tag: meter.tag,
            aprox: meter.aprox,
            min: meter.min,
            max: meter.max
        };

        if(!meterid){
            meterid = firebase.database().ref().child('meters').push().key;
        }

        let updates = {}
        updates['/meters/' + meterid] = meter_data

        let meter_ref = firebase.database().ref()

        meter_ref.update(updates)
            .then(function () {
                return { success: true, message: 'Meter created'};
            })
            .catch(function (error) {
                return {success : false, message: `Creation failed: ${error.message}`}
            })
    }

    function remove_meter() {
        if (!meterid) {
            return {success: false, message: 'Invalid Meter'}
        }

        let meter_ref = firebase.database().ref('/meters/' + meterid)

        meter_ref.remove()
            .then(function () {
                return { success: true, message: 'Meter removed'};
            })
            .catch(function (error) {
                return {success : false, message: `Remove failed: ${error.message}`}
            })
    }

    function update_meter(value) {
        if (!meterid) {
            return {success: false, message: 'Invalid Meter'}
        }

        let meter_ref = firebase.database().ref('/meters/' + meterid)

        let updates = {}
        updates['/value/'] = value;

        meter_ref.update(updates)
            .then(function () {
                return { success: true, message: 'Meter updated'};
            })
            .catch(function (error) {
                return {success : false, message: `Update failed: ${error.message}`}
            })
    }


    async function listen_meter() {
        if (!meterid) {
            return {success: false, message: 'Invalid Meter'}
        }

        let meter_ref = firebase.database().ref('/meters/' + meterid)

        meter_ref.once('child_changed')
            .then(function (snapshot) {

                if (snapshot.key == 'value') {
                    console.log('Value changed', snapshot.val())
                    return {success: true, message: 'Value Update', data: snapshot.val()}
                }
            })
            .catch(function (error) {
                return {success : false, message: `Invalid data: ${error.message}`}
            })
    }

    meters_database.new = new_meter
    meters_database.remove = remove_meter
    meters_database.update = update_meter
    meters_database.listen_meter = listen_meter
})()

var velocidade = { 
    name: 'Vehicle speed', 
    value: 100,
    tag: ".velocidade",
    aprox: 2,
    min: 0,
    max: 120
}

meters_database.new(velocidade)

function renderScreen() {

    for (const meterId in meters_database) {
        const meter = meters_database[meterId]
        document.querySelector(meter.tag + 'span').innerHTML = meter.value
        console.log(meter.tag + " " + meter.value)
    }

    setTimeout(() => {
        requestAnimationFrame(() => renderScreen(value))
    }, 500);
}