//program showcasing cards and deck classes

#include "cards.cpp"

int main(){
    std::vector<std::shared_ptr<Card>> card_collection;
    //card_collection.push_back(std::make_shared<PayCard>("Your cousin forgot their wallet! You happily pay for dinner. PAY 11$.", 22));
    //card_collection.push_back(std::make_shared<GetMoneyCard>("You have won second prize in a beauty contest. COLLECT 11$", 69));
    //card_collection.push_back(std::make_shared<GetOutOfJailCard>("Get Out of Jail Free"));
    //card_collection.push_back(std::make_shared<MoveCard>("Blaring music late at night? Your neighbors do not approve. GO TO JAIL."));
    Deck<Card> deck;
    //for (auto& card : deck.deck){
    //    std::cout << typeid(*card).name();
    //}
    deck.add_cards(deck.load_cards_from_file("deck.txt"));
    //deck.load_cards_from_file("deck.txt");
    deck.print_deck();
    //deck.shuffle();
    //deck.draw_card()->effect();
    //deck.save_deck("deck.txt");
    return 0;
}