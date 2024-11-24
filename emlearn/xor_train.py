import logging
import emlearn
import numpy
from sklearn.ensemble import RandomForestClassifier
from sklearn.metrics import get_scorer

# Configure el logger
logging.basicConfig(level=logging.INFO)
logger = logging.getLogger(__name__)

# Genere un dataset simple con la tabla de verdad XOR
def make_xor(lower=0.0, upper=1.0, threshold=0.5, samples=100, seed=42):
    rng = numpy.random.RandomState(seed)
    X = rng.uniform(lower, upper, size=(samples, 2))
    y = numpy.logical_xor(X[:, 0] > threshold, X[:, 1] > threshold)
    # convierta a int16 con un rango de 8 bit. [0.0-1.0] -> [0-255]
    X = (X * 255).astype(numpy.int16)
    return X, y

X, y = make_xor()

# Entrene el modelo
logger.info("Entrenando el modelo...")
estimator = RandomForestClassifier(n_estimators=3, max_depth=3, max_features=2, random_state=1)
estimator.fit(X, y)
score = get_scorer('f1')(estimator, X, y)
assert score > 0.90, score # Verifique que la función si fue aprendida

# Convierta el modelo emlearn
path = 'emlearn/src/xor_model.h'
cmodel = emlearn.convert(estimator, method='inline')
cmodel.save(file=path, name='xor_model')
assert os.path.exists(model_filename)
logger.info(f'Modelo guardado en el directorio {path}')