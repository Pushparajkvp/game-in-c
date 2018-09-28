# SDL 2 Player Game

> A simple 2 player platformer game with shooting capabilities.

## Index


DISCLAIMER: Anna University has closed the portal through which this script accessed
semester results without Date of Birth. This will start working when Anna University
opens the portal back for the next semester results.

AU Portal: `http://aucoe.annauniv.edu/cgi-bin/result/cgrade.pl?regno=` (If this works, the app will too)

![](screenshot.png)

# AUScraper

> A simple app that generates an excel file for a range of register numbers
> fetched from Anna University server.

## Index
  * [Demo](#demo)
  * [Technology Colophon](#colophon)
  * [API Endpoints](#api)
  * [Installation](#installation)
  * [Deployment](#deploy)
  * [Contribute](#contribute)
  * [License](#license)

## Demo <a name="demo"></a>
Check it out: [https://auscraper.herokuapp.com/](https://auscraper.herokuapp.com/)

## Technology Colophon <a name="colophon"></a>
  * Backend -
    * PHP 7, Composer
    * phroute - routing
    * guzzle - To send asynchronous request
    * PHPExcel - To generate Excel file
    * Gulp - Task Runner

  * Frontend -
    * scss - CSS preprocessor
    * browserify, babble - ES6 support
    * JQuery, materialize.css, Modernizr, Normalize.css

## API Endpoints <a name="api"></a>

```
POST /api/json HTTP/1.1
```

Request body:

```
{
  'regno': [Register Number],
  'offset': [Number of results to be downloaded after the given `regno`. range: 0 - 99]
}
```

Response:
  * onsuccess - Array of JSON results.
  * onerror - Response Code: 400[Bad Request]. responseBody.error -> Error Message.

--------------------------------------------------------------------------------

```
POST /api/excel HTTP/1.1
```

Request body:

```json
{
  'regno': [Register Number],
  'offset': [Number of results to be downloaded after the given `regno`. range: 0 - 99]
}
```

Response:
  * onsuccess - `.xlsx` file with results. `Content-Type: application/vnd.openxmlformats-officedocument.spreadsheetml.sheet`
  * onerror - Response Code: 400[Bad Request]. responseBody.error -> Error Message.

Note: Use `resources/scripts/app.js` as reference to send request via web client.

## Installation <a name="installation"></a>
  1. Install Apache 2, PHP 7 and Composer

  2. Clone this repository

  ```
    $ git clone https://github.com/AravindVasudev/AUScraper.git
    $ cd AUScraper
  ```

  3. Install Dependencies

  ```
    $ composer install
    $ npm install
  ```

## Deploying in Heroku <a name="deploy"></a>
  1. Following Installation, Install `Heroku Toolbelt` and `Git Client`.

  2. Create a new Heroku App and push the code

  ```
  $ heroku create
  $ git push heroku master
  ```

## Contribute <a name="contribute"></a>
  You are always welcome to open an issue or provide a pull-request!

## License <a name="license"></a>
  Built under [MIT](http://www.opensource.org/licenses/mit-license.php) license.