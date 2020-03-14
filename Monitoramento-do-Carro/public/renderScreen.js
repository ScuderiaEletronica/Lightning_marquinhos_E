(function () {
    function renderScreen(){



        setTimeout(() => {
            requestAnimationFrame(() => renderScreen(value))
        }, 500);
    }
})()