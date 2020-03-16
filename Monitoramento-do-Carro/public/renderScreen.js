export default function renderScreen(meters_database) {

    for (const meterId in meters_database) {
        const meter = meters_database[meterId]
        document.querySelector(meter.tag + 'span').innerHTML = meter.value
    }

    setTimeout(() => {
        requestAnimationFrame(() => renderScreen(value))
    }, 500);
}