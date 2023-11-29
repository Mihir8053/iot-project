import joblib
import pandas as pd
from sklearn.model_selection import train_test_split
from sklearn.linear_model import LinearRegression
from sklearn import linear_model
from sklearn.metrics import mean_squared_error, r2_score
import numpy as np
from sklearn.model_selection import cross_val_score


df = pd.read_excel('altered_wqi.xlsx')

columns_to_keep =['Temperature','Turbidity','ph','atWQI']
df=df[columns_to_keep]
X = df.iloc[:, :-1]  # Independent variables
y = df['atWQI']  # Dependent variable


X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.30, random_state=42)


#lasso regression
lmodel=linear_model.Lasso(alpha=10,max_iter=100,tol=0.1)
lmodel.fit(X_train,y_train)
print("TEST")
print(lmodel.score(X_test,y_test))
print("TRAIN")
print(lmodel.score(X_train,y_train))
y_pred_lasso = lmodel.predict(X_test)
y_pred_train=lmodel.predict(X_train)
mse = mean_squared_error(y_test, y_pred_lasso)
rmse = np.sqrt(mse)
r2 = r2_score(y_test, y_pred_lasso)
r2_train=r2_score(y_train, y_pred_train)
print(mse)
print(rmse)
print(r2)
print(r2_train)

joblib.dump(lmodel, 'pretrained_model.joblib')
