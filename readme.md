# Arduino REST API Server

J'ai récupéré le travail de [fcaldas](https://github.com/fcaldas) pour pouvoir utilisé rapidement la connexion du arduino sur le reseau et la gestion des routes.

Prévu pour un arduino mega, le script permet de commander la valeur de chaque pin digital par un envoi de requet POST en Json.

exemple: 
```
{"pin": 7, "value": "HIGH"}
```

