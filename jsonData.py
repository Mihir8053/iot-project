import pandas as pd
from pymongo import MongoClient

# Read Excel file into a DataFrame
df = pd.read_excel('altered_wqi.xlsx')

json_data = df.to_dict(orient='records')

client = MongoClient('mongodb://localhost:27017/')
db = client['iot-project']
collection = db['water quality index']
collection.insert_many(json_data)
