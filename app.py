import requests

url = 'https://api.lafactory.co/crm-backend'

res = requests.get(url)
print(res.text)