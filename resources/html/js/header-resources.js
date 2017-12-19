/*var i = 0;
window.setInterval(oneSecondFunction, 500);

function oneSecondFunction() {
    var metal = document.getElementById("metal-value");
    var crystal = document.getElementById("crystal-value");
    var deuterium = document.getElementById("deuterium-value");
    var antimatter = document.getElementById("antimatter-value");
    var energy = document.getElementById("energy-value");
    metal.innerHTML = i;
    crystal.innerHTML = (i)*2;
    deuterium.innerHTML = Math.round((i)*4 / 1.5);
    antimatter.innerHTML = Math.round((i) / (Math.sqrt(i) + 1));
    energy.innerHTML = "42/" + i;
    i += 10;
}*/

function updateResources(iron, crystal, iridium, antimatter, energy) {
    document.getElementById("metal-value").innerText = iron;
    document.getElementById("crystal-value").innerText = crystal;
    document.getElementById("deuterium-value").innerText = iridium; // todo rename to iridium
    document.getElementById("antimatter-value").innerText = antimatter;
    document.getElementById("energy-value").innerText = energy;
}