#include "../../06_Service/Inc/version_service.h"

int VERSION_Compare(const app_metadata_t *a, const app_metadata_t *b)
{
    if (a->version_major != b->version_major)
        return (a->version_major > b->version_major) ? 1 : -1;

    if (a->version_minor != b->version_minor)
        return (a->version_minor > b->version_minor) ? 1 : -1;

    if (a->version_patch != b->version_patch)
        return (a->version_patch > b->version_patch) ? 1 : -1;

    return 0;
}
