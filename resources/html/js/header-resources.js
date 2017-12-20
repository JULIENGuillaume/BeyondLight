window.setInterval(updateLoop, 1000);

function updateResources(iron, crystal, iridium, antimatter, energy) {
    document.getElementById("metal-value").innerText = iron;
    document.getElementById("crystal-value").innerText = crystal;
    document.getElementById("deuterium-value").innerText = iridium; // todo rename to iridium
    document.getElementById("antimatter-value").innerText = antimatter;
    document.getElementById("energy-value").innerText = energy;
}

function updateLoop() {
        var request_id = window.cefQuery({
            request: 'update-player-resources',
            persistent: true,
            onSuccess: function(response) {
                var resources = response.split(":");
                updateResources(resources[0], resources[1], resources[2], resources[3], resources[4]);
            },
            onFailure: function(error_code, error_message) {
                console.log("cannot update player resources");
            }
        });
}