from mock import patch

from turbodbc.cursor import _has_numpy_support

import pytest

# Skip all parquet tests if we can't import pyarrow.parquet
pytest.importorskip('numpy')

# Ignore these with pytest ... -m 'not parquet'
numpy = pytest.mark.numpy


# Skip all parquet tests if we can't import pyarrow.parquet
@pytest.mark.numpy
def test_has_numpy_support_fails():
    with patch("builtins.__import__", side_effect=ImportError):
        assert _has_numpy_support() == False


@pytest.mark.numpy
def test_has_numpy_support_succeeds():
    assert _has_numpy_support() == True
