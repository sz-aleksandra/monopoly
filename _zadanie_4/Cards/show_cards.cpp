#include "cards.cpp"

int main(){
    std::vector<std::shared_ptr<Card>> card_collection;
    card_collection.push_back(std::make_shared<PayCard>("Your cousin forgot their wallet! You happily pay for dinner. PAY 11$."));
    card_collection.push_back(std::make_shared<GetMoneyCard>("You have won second prize in a beauty contest. Collect 11$"));
    card_collection.push_back(std::make_shared<GetOutOfJailCard>("Get Out of Jail Free"));
    card_collection.push_back(std::make_shared<MoveCard>("Blaring music late at night? Your neighbors do not approve. GO TO JAIL."));
    Deck<Card> deck(card_collection);
    deck.add_cards(deck.load_cards_from_file("deck.txt"));
    /*for (const auto& card : card_collection) {
        card->effect("ola", 2);
    }
    card_collection.at(0)->effect("ola", 2);*/
    for (const auto& card : deck.deck) {
        card->effect("ola", 11);
    }
    deck.save_deck("deck.txt");
    return 0;
}