# prediction.py

import joblib
import numpy as np
import sys


def predict_water_quality(features):
    # Load the model from the file
    loaded_model = joblib.load('pretrained_model.joblib')

    # features should be a 1D array-like object
    new_input = np.array(features).reshape(1, -1)

    # Make predictions with the loaded model
    prediction = loaded_model.predict(new_input)
    return prediction[0]  # Assuming a single prediction is expected


if __name__ == "__main__":
    # Read input data from command line arguments
    print("python script")
    if len(sys.argv) == 4:
        feature1, feature2, feature3 = map(float, sys.argv[1:])
    else:
        print("Usage: python prediction.py temperature turbidity ph")
        sys.exit(1)

    # Perform prediction
    prediction = predict_water_quality([feature1, feature2, feature3])

    # Print the prediction
    print("Prediction:", prediction)
