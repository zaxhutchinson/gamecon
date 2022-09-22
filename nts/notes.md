Commodities:
    * Register with the system
    * 


Producer: Adds items to the system.
Consumer: Removes items to the system.
Trader: Moves from node to node fulfilling requests.
    Traders can also be merchants.
Merchant: Sells to consumers/traders.
    Receives items from traders per requests


Network: 
    Nodes: Nodes are merchants.
    Edges: Traders


Request tokens consist of an item type, sub-type and location.


Producers develop a stock pile which is bought by traders.
Traders bring the stock to merchants.
Consumers visit merchants to buy specific items they want/need.
    -If consumers get what they want, the need is filled.
    -If they do not get what they want, they leave a request token with the merchant.
    -When the next trader visits, he will copy all requests he doesn't already have times some number. A merchant doesn't just order the actual requests but some quantity above. The logic is, if they have requests, they will get more.
    -When he copies a request, he adds the location of origin.
    -When the trader arrives at another merchant, he will copy to the merchant his reqeusts as if he were a consumer.
    - This cycle continues and that merchant treats the trader's request as if he were a consumer. Trader requests, however, might not be scaled as pure consumer requests are.
    - A trader makes purchases based on requests in his possession.
    - No money changes hands. Money is abstracted away in two ways. How many requests a consumer makes and how much a producer produces.

If done right, this will create local needs and surpluses. The player can then exploit this. For example, in a war zone, arrows might be rare.


Price can be some combination of base value, open requests and recent requests.
Maybe: base value * (recent requests / stock)
 

Actions:

* General
    - Register items
* Consumer
    - Make requests
* Producer
    - Register which items they generate and capacity.
    - Generate items into local stockpile
* Trader
    - Move from one node to another.
    - Make requests from merchants
    - Copy requests from merchants
    - Copy requests to merchants
* Merchants
    - Take requests
    - Copy requests to merchants
