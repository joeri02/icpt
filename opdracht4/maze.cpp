#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {
    // Inventory 
    bool has_fakkel = false;
    bool has_sleutel = false;
    bool has_zwaard = false;

    // Path history
    vector<string> path;

    string keuze;

    cout << "=== WELKOM IN HET DOOLHOF ===" << endl;
    cout << "Gebruik kompasrichtingen: noord, zuid, oost, west" << endl;
    cout << "Type 'inventory' om je voorwerpen te zien" << endl;
    cout << "Type 'pakken' om voorwerpen op te pakken" << endl << endl;

kamer1_entree:
    cout << "\n--- KAMER 1: ENTREE ---" << endl;
    cout << "Je staat in de entree van het doolhof." << endl;
    cout << "Er is een gang naar het NOORDEN." << endl;
    cout << "Welke richting? ";
    cin >> keuze;

    if (keuze == "inventory") {
        cout << "\nInventory: ";
        if (has_fakkel) cout << "fakkel ";
        if (has_sleutel) cout << "sleutel ";
        if (has_zwaard) cout << "zwaard ";
        if (!has_fakkel && !has_sleutel && !has_zwaard) cout << "leeg";
        cout << endl;
        goto kamer1_entree;
    }

    if (keuze == "noord") {
        path.push_back("noord");
        goto kamer2_hal;
    }

    cout << "Ongeldige richting!" << endl;
    goto kamer1_entree;

kamer2_hal:
    cout << "\n--- KAMER 2: GROTE HAL ---" << endl;
    cout << "Een grote hal met hoge zuilen." << endl;
    cout << "Je ziet een FAKKEL aan de muur!" << endl;
    cout << "Gangen: NOORD, OOST, ZUID" << endl;
    cout << "Welke richting? ";
    cin >> keuze;

    if (keuze == "inventory") {
        cout << "\nInventory: ";
        if (has_fakkel) cout << "fakkel ";
        if (has_sleutel) cout << "sleutel ";
        if (has_zwaard) cout << "zwaard ";
        if (!has_fakkel && !has_sleutel && !has_zwaard) cout << "leeg";
        cout << endl;
        goto kamer2_hal;
    }

    if (keuze == "pakken") {
        if (!has_fakkel) {
            has_fakkel = true;
            cout << "Je hebt de FAKKEL gepakt!" << endl;
        } else {
            cout << "Je hebt de fakkel al!" << endl;
        }
        goto kamer2_hal;
    }

    if (keuze == "noord") {
        path.push_back("noord");
        goto kamer3_donker;
    }
    if (keuze == "oost") {
        path.push_back("oost");
        goto kamer4_schatkamer;
    }
    if (keuze == "zuid") {
        path.push_back("zuid");
        goto kamer1_entree;
    }

    cout << "Ongeldige richting!" << endl;
    goto kamer2_hal;

kamer3_donker:
    cout << "\n--- KAMER 3: DONKERE KAMER ---" << endl;

    if (!has_fakkel) {
        cout << "Het is aardedonker hier!" << endl;
        cout << "Je hebt een FAKKEL nodig om verder te gaan." << endl;
        cout << "Je gaat terug naar de hal." << endl;
        goto kamer2_hal;
    }

    cout << "Je steekt de fakkel aan. De kamer wordt verlicht!" << endl;
    cout << "Je ziet een SLEUTEL op de grond liggen." << endl;
    cout << "Gangen: OOST, ZUID" << endl;
    cout << "Welke richting? ";
    cin >> keuze;

    if (keuze == "inventory") {
        cout << "\nInventory: ";
        if (has_fakkel) cout << "fakkel ";
        if (has_sleutel) cout << "sleutel ";
        if (has_zwaard) cout << "zwaard ";
        if (!has_fakkel && !has_sleutel && !has_zwaard) cout << "leeg";
        cout << endl;
        goto kamer3_donker;
    }

    if (keuze == "pakken") {
        if (!has_sleutel) {
            has_sleutel = true;
            cout << "Je hebt de SLEUTEL gepakt!" << endl;
        } else {
            cout << "Je hebt de sleutel al!" << endl;
        }
        goto kamer3_donker;
    }

    if (keuze == "oost") {
        path.push_back("oost");
        goto kamer5_gang;
    }
    if (keuze == "zuid") {
        path.push_back("zuid");
        goto kamer2_hal;
    }

    cout << "Ongeldige richting!" << endl;
    goto kamer3_donker;

kamer4_schatkamer:
    cout << "\n--- KAMER 4: SCHATKAMER ---" << endl;

    if (!has_sleutel) {
        cout << "De deur is op slot!" << endl;
        cout << "Je hebt een SLEUTEL nodig om binnen te komen." << endl;
        cout << "Je gaat terug naar de hal." << endl;
        goto kamer2_hal;
    }

    cout << "Je gebruikt de sleutel om de deur te openen!" << endl;
    cout << "Een kamer vol schatten! Maar ook... een wachter!" << endl;
    cout << "Gangen: NOORD, ZUID, WEST" << endl;
    cout << "Welke richting? ";
    cin >> keuze;

    if (keuze == "inventory") {
        cout << "\nInventory: ";
        if (has_fakkel) cout << "fakkel ";
        if (has_sleutel) cout << "sleutel ";
        if (has_zwaard) cout << "zwaard ";
        if (!has_fakkel && !has_sleutel && !has_zwaard) cout << "leeg";
        cout << endl;
        goto kamer4_schatkamer;
    }

    if (keuze == "noord") {
        path.push_back("noord");
        goto kamer6_wachter;
    }
    if (keuze == "zuid") {
        path.push_back("zuid");
        goto kamer7_opslagruimte;
    }
    if (keuze == "west") {
        path.push_back("west");
        goto kamer2_hal;
    }

    cout << "Ongeldige richting!" << endl;
    goto kamer4_schatkamer;

kamer5_gang:
    cout << "\n--- KAMER 5: SMALLE GANG ---" << endl;
    cout << "Een smalle gang met vochtige muren." << endl;
    cout << "Gangen: ZUID, WEST" << endl;
    cout << "Welke richting? ";
    cin >> keuze;

    if (keuze == "inventory") {
        cout << "\nInventory: ";
        if (has_fakkel) cout << "fakkel ";
        if (has_sleutel) cout << "sleutel ";
        if (has_zwaard) cout << "zwaard ";
        if (!has_fakkel && !has_sleutel && !has_zwaard) cout << "leeg";
        cout << endl;
        goto kamer5_gang;
    }

    if (keuze == "zuid") {
        path.push_back("zuid");
        goto kamer6_wachter;
    }
    if (keuze == "west") {
        path.push_back("west");
        goto kamer3_donker;
    }

    cout << "Ongeldige richting!" << endl;
    goto kamer5_gang;

kamer6_wachter:
    cout << "\n--- KAMER 6: WACHTKAMER ---" << endl;

    if (!has_zwaard) {
        cout << "Een gevaarlijke wachter blokkeert de weg!" << endl;
        cout << "Je hebt een ZWAARD nodig om langs te komen." << endl;
        cout << "Je vlucht terug!" << endl;
        goto kamer4_schatkamer;
    }

    cout << "Je gebruikt het zwaard om de wachter te verslaan!" << endl;
    cout << "De uitgang is dichtbij!" << endl;
    cout << "Gangen: OOST, NOORD, ZUID" << endl;
    cout << "Welke richting? ";
    cin >> keuze;

    if (keuze == "inventory") {
        cout << "\nInventory: ";
        if (has_fakkel) cout << "fakkel ";
        if (has_sleutel) cout << "sleutel ";
        if (has_zwaard) cout << "zwaard ";
        if (!has_fakkel && !has_sleutel && !has_zwaard) cout << "leeg";
        cout << endl;
        goto kamer6_wachter;
    }

    if (keuze == "oost") {
        path.push_back("oost");
        goto kamer8_uitgang;
    }
    if (keuze == "noord") {
        path.push_back("noord");
        goto kamer5_gang;
    }
    if (keuze == "zuid") {
        path.push_back("zuid");
        goto kamer4_schatkamer;
    }

    cout << "Ongeldige richting!" << endl;
    goto kamer6_wachter;

kamer7_opslagruimte:
    cout << "\n--- KAMER 7: OPSLAGRUIMTE ---" << endl;
    cout << "Een stoffige opslagruimte vol oude spullen." << endl;
    cout << "Je ziet een ZWAARD tegen de muur!" << endl;
    cout << "Gangen: NOORD, OOST" << endl;
    cout << "Welke richting? ";
    cin >> keuze;

    if (keuze == "inventory") {
        cout << "\nInventory: ";
        if (has_fakkel) cout << "fakkel ";
        if (has_sleutel) cout << "sleutel ";
        if (has_zwaard) cout << "zwaard ";
        if (!has_fakkel && !has_sleutel && !has_zwaard) cout << "leeg";
        cout << endl;
        goto kamer7_opslagruimte;
    }

    if (keuze == "pakken") {
        if (!has_zwaard) {
            has_zwaard = true;
            cout << "Je hebt het ZWAARD gepakt!" << endl;
        } else {
            cout << "Je hebt het zwaard al!" << endl;
        }
        goto kamer7_opslagruimte;
    }

    if (keuze == "noord") {
        path.push_back("noord");
        goto kamer4_schatkamer;
    }
    if (keuze == "oost") {
        path.push_back("oost");
        goto kamer8_uitgang;
    }

    cout << "Ongeldige richting!" << endl;
    goto kamer7_opslagruimte;

kamer8_uitgang:
    cout << "\n--- KAMER 8: UITGANG ---" << endl;
    cout << "Je hebt de uitgang gevonden!" << endl;
    cout << "GEFELICITEERD! Je bent uit het doolhof ontsnapt!" << endl << endl;

    cout << "Je hebt het volgende pad gevolgd:" << endl;
    for (size_t i = 0; i < path.size(); i++) {
        cout << (i + 1) << ". " << path[i] << endl;
    }

    return 0;
}
