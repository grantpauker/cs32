/*
 * Return true if the somePredicate function returns false for at
 * least one of the array elements, false otherwise.
 */
bool anyFalse(const double a[], int n)
{
    if (n <= 0)
    {
        return false;
    }
    if (!somePredicate(*a))
    {
        return true;
    }
    return anyFalse(a + 1, n - 1);
}

/*
 * Return the number of elements in the array for which the
 * somePredicate function returns false.
 */
int countFalse(const double a[], int n)
{
    if (n <= 0)
    {
        return 0;
    }
    return !somePredicate(*a) + countFalse(a + 1, n - 1);
}

/*
 * Return the subscript of the first element in the array for which
 *the somePredicate function returns true. If there is no such
 * element, return -1.
 */
int firstTrue(const double a[], int n)
{
    if (n <= 0)
    {
        return -1;
    }
    int ret = firstTrue(a + 1, n - 1);
    if (somePredicate(*a))
    {
        return 0;
    }
    else if (ret == -1)
    {
        return -1;
    }
    return 1 + ret;
}

/*
 * Return the subscript of the largest element in the array (i.e.,
 * return the smallest subscript m such that a[m] >= a[k] for all
 * k such that k >= 0 and k < n). If there is no such subscript,
 * return -1.
 */
int locateMax(const double a[], int n)
{
    if (n <= 0)
    {
        return -1;
    }
    if (n == 1)
    {
        return 0;
    }
    int i0 = locateMax(a, n / 2);
    int i1 = n / 2 + locateMax(a + n / 2, n - n / 2);
    return a[i0] >= a[i1] ? i0 : i1;
}

/*
 * If all n2 elements of a2 appear in the n1 element array a1, in
 * the same order (though not necessarily consecutively), then
 * return true; otherwise (i.e., if the array a1 does not contain
 * a2 as a not-necessarily-contiguous subsequence), return false.
 * (Of course, if a2 is empty (i.e., n2 is 0), return true.)
 */
bool contains(const double a1[], int n1, const double a2[], int n2)
{
    if (n2 <= 0)
    {
        return true;
    }
    if (n1 < n2)
    {
        return false;
    }
    if (a1[0] == a2[0])
    {
        return contains(a1 + 1, n1 - 1, a2 + 1, n2 - 1);
    }
    else
    {
        return contains(a1 + 1, n1 - 1, a2, n2);
    }
}
